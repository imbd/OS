#include "tmpfs.h"
#include "lock.h"
#include "strings.h"
#include "list.h"
#include "allocator.h"
#include "avl_tree.h"
#include "threads.h"
#include <stddef.h>

typedef struct {
	void * buffer;
	size_t size;
}reg_file_data_t;

typedef struct {
	void * parent;
	struct list_head children_head;
}dir_file_data_t;

typedef struct {
	void * file_data;
	ftype type;
	int ref_cnt;
}inode_t;

typedef struct {
	inode_t * inode;
	const char * file_path;
	struct list_head sibling;
}fpath_node_t;

typedef struct {
	int type;
	fpath_node_t * node;
	size_t writing_offset;
	size_t reading_offset;
	void * writing_buffer;
}file_description_t;

#define MAX_OPENED_DESCRIPTORS 1000
static file_description_t fdtable_descriptions[MAX_OPENED_DESCRIPTORS];
static int fdtable_descriptors_stack[MAX_OPENED_DESCRIPTORS];
static int fdtable_descriptors_stack_ptr = 0;

static thread_mutex * mutex  = NULL;
static avl_tree_t * fpaths_avl = NULL;

static const size_t REG_FILE_INITIAL_SIZE = 1;

static reg_file_data_t * reg_file_data_create() {
	reg_file_data_t * reg_file_data = malloc(sizeof(reg_file_data_t));
	reg_file_data->size = REG_FILE_INITIAL_SIZE;
	reg_file_data->buffer = malloc(reg_file_data->size);
	return reg_file_data;
}

static void reg_file_data_remove(reg_file_data_t * data) {
	free(data->buffer);
	free(data);
}

static void reg_file_data_write(reg_file_data_t * file_data, void * buffer, size_t new_size) {
	if(file_data->size < new_size) {
		file_data->buffer = realloc(file_data->buffer, new_size);
		file_data->size = new_size;
	}
	memcpy(file_data->buffer, buffer, new_size);
}

static void reg_file_data_read(reg_file_data_t * file_data, size_t offset, void * buffer, size_t size) {
	memcpy(buffer, (char * )file_data->buffer + offset, size);
}

static dir_file_data_t *  dir_file_data_create(void * parent) {
	dir_file_data_t * dir_file_data = malloc(sizeof(dir_file_data));
	dir_file_data->parent = parent;
	list_init(&dir_file_data->children_head);
	return dir_file_data;
}

static void dir_file_data_remove(dir_file_data_t * data) {
	free(data);
}

static inode_t *  inode_new_reg() {
	inode_t * inode = malloc(sizeof(inode_t));
	inode->type = IS_REG;
	inode->file_data = reg_file_data_create();
	inode->ref_cnt = 0;
	return inode;
}

static inode_t * inode_new_dir(void * parent) {
	inode_t * inode = malloc(sizeof(inode_t));
	inode->type = IS_DIR;
	inode->file_data = dir_file_data_create(parent);
	inode->ref_cnt = 0;
	return inode;
}

static void inode_remove(inode_t * inode) {
	if(inode->type == IS_DIR){
		dir_file_data_remove(inode->file_data);
	} else {
		reg_file_data_remove(inode->file_data);
	}
	free(inode);
}

static void inode_remove_link(inode_t * inode) {
	if((--inode->ref_cnt) == 0) {
		inode_remove(inode);
	}
}

static fpath_node_t * fpath_node_new(inode_t * inode, const char * path) {
	fpath_node_t * node = malloc(sizeof(fpath_node_t));
	node->inode = inode;
	node->file_path = path;
	list_init(&node->sibling);
	inode->ref_cnt++;
	return node;
}


static void fpath_node_remove(fpath_node_t * node) {
	inode_remove_link(node->inode);
	list_del(&node->sibling);
	free((void *)node->file_path);
	free(node);
}

static void file_description_clear_buffer(file_description_t * file_desctiption) {
	if(file_desctiption->writing_buffer != NULL) {
		free(file_desctiption->writing_buffer);
		file_desctiption->writing_buffer = NULL;
	}
}

static void file_description_flush(file_description_t * file_description) {
	if(file_description->node->inode->type == IS_REG && (CHECK_FLAG(file_description->type, OP_WRITE))) {
		reg_file_data_write(file_description->node->inode->file_data, file_description->writing_buffer, file_description->writing_offset);
	}
}

static void file_description_write(file_description_t * file_description, void * buf, size_t size) {
	file_description->writing_buffer = realloc(file_description->writing_buffer, file_description->writing_offset + size);
	memcpy((char *)file_description->writing_buffer + file_description->writing_offset, buf, size);
	file_description->writing_offset += size;
}

static void file_description_read(file_description_t * file_description, void * buf, size_t size) {
	reg_file_data_read(file_description->node->inode->file_data,
			       file_description->reading_offset,
				   buf,
				   size);
	file_description->reading_offset += size;
}

static void file_description_seek(file_description_t * file_description, size_t offset){
	file_description->reading_offset = offset;
}

static void file_description_init(file_description_t * file_description, fpath_node_t * node, int fopen_type) {
	file_description->writing_buffer = malloc(REG_FILE_INITIAL_SIZE);
	file_description->writing_offset = 0;
	file_description->reading_offset = 0;
	file_description->node = node;
	file_description->type = fopen_type;
}

static file_description_t * fdtable_get_description(int fd) {
	return &fdtable_descriptions[fd];
}

static int fdtable_get_free(){
	return fdtable_descriptors_stack[fdtable_descriptors_stack_ptr--];
}

static void fdtable_put(int fd) {
	fdtable_descriptors_stack[++fdtable_descriptors_stack_ptr] = fd;
}

static void fdtable_init() {
	for(int i = 0; i < MAX_OPENED_DESCRIPTORS; i++) {
		fdtable_descriptors_stack[i] = i;
	}
	fdtable_descriptors_stack_ptr = MAX_OPENED_DESCRIPTORS - 1;
}


static char * last_dir(const char * path) {
	int pos = str_find_last(path, '/', strlen(path) - 1);
	if(pos == -1)
		return NULL;
	char * new_str = malloc((pos+2) * sizeof(char));
	memcpy(new_str, path, pos + 1);
	new_str[pos + 1] = '\0';
	return new_str;
}

static void add_link(const char * path_arg, inode_t * link) {
	char * path = str_cpy(path_arg);
	char * last_dir_f = last_dir(path);
	if(last_dir_f == NULL) /* adding rootdir now */  {
		avl_tree_insert(fpaths_avl, (void *)path, fpath_node_new(link, path));
	} else {
		fpath_node_t * dir_node = avl_tree_find(fpaths_avl, last_dir_f);
		fpath_node_t * new_node_g = fpath_node_new(link, path);
		avl_tree_insert(fpaths_avl, (void *)path, new_node_g);
		list_add(&new_node_g->sibling, &((dir_file_data_t *) dir_node->inode->file_data)->children_head);
	}
	free(last_dir_f);
}

static void remove_link(const char * path) {
	avl_tree_remove(fpaths_avl, (void *)path);
	fpath_node_remove(avl_tree_find(fpaths_avl, (void*)path));
}

static bool isdir_empty(const char * path) {
	return list_empty(&((dir_file_data_t *)(
			(fpath_node_t *)avl_tree_find(fpaths_avl, (void *)path))->inode->file_data)->children_head);
}

void tmpfs_set_sync() {
	mutex = thread_mutex_create();
}

static void tmpfs_lock() {
	if(mutex != NULL) {
		thread_mutex_lock(mutex);
	}
}

static void tmpfs_unlock() {
	if(mutex != NULL) {
		thread_mutex_unlock(mutex);
	}
}


void tmpfs_create(const char * path) {
	tmpfs_lock();
	add_link(path, inode_new_reg());
	tmpfs_unlock();
}

void tmpfs_remove(const char * path) {
	tmpfs_lock();
	remove_link(path);
	tmpfs_unlock();
}

void tmpfs_link(const char * oldpath, const char * newpath) {
	tmpfs_lock();
	fpath_node_t * node = avl_tree_find(fpaths_avl, (void *)oldpath);
	add_link(newpath, node->inode);
	tmpfs_unlock();
}

int tmpfs_open(const char * path, int type) {
	tmpfs_lock();
	int fd = fdtable_get_free();
	file_description_init(fdtable_get_description(fd), avl_tree_find(fpaths_avl, (void *)path), type);
	tmpfs_unlock();
	return fd;
}

void tmpfs_close(int fd) {
	tmpfs_lock();
	file_description_t * file_description = fdtable_get_description(fd);
	file_description_flush(file_description);
	file_description_clear_buffer(file_description);
	fdtable_put(fd);
	tmpfs_unlock();
}

void tmpfs_read(int fd, void * buf, size_t size) {
	tmpfs_lock();
	file_description_read(fdtable_get_description(fd), buf, size);
	tmpfs_unlock();
}

void tmpfs_seek(int fd, size_t offset) {
	tmpfs_lock();
	file_description_seek(fdtable_get_description(fd), offset);
	tmpfs_unlock();
}

size_t tmpfs_get_reading_offset(int fd) {
	tmpfs_lock();
	size_t ret = fdtable_get_description(fd) -> reading_offset;
	tmpfs_unlock();
	return ret;
}

void tmpfs_write(int fd, void * buf, size_t size) {
	tmpfs_lock();
	file_description_write(fdtable_get_description(fd), buf, size);
	tmpfs_unlock();
}

void tmpfs_mkdir(const char * path) {
	tmpfs_lock();
	char * last_dir_f = last_dir(path);
	add_link(path, inode_new_dir(((fpath_node_t *)avl_tree_find(fpaths_avl, last_dir_f))->inode));
	free(last_dir_f);
	tmpfs_unlock();
}

void tmpfs_rmdir(const char * path) {
	tmpfs_lock();
	if(isdir_empty(path)) {
		remove_link(path);
	}
	tmpfs_unlock();
}

dir_t * tmpfs_opendir(const char * path) {
	tmpfs_lock();
	dir_t * ret = malloc(sizeof(dir_t));
	ret->fd = tmpfs_open(path, OP_READ);
	ret->position = &((dir_file_data_t *)fdtable_get_description(ret->fd)->node->inode->file_data)->children_head;
	ret->cur_dirrent = NULL;
	tmpfs_unlock();
	return ret;
}

dirent_t * tmpfs_readdir(dir_t * opened_dir) {
	tmpfs_lock();
	if(opened_dir->cur_dirrent == NULL) {
		opened_dir->cur_dirrent = malloc(sizeof(dirent_t));
	}
	opened_dir->position = opened_dir->position->next;
	if(opened_dir->position == &((dir_file_data_t *)fdtable_get_description(opened_dir->fd)->node->inode->file_data)->children_head) {
		free(opened_dir->cur_dirrent);
		opened_dir->cur_dirrent = NULL;
		tmpfs_unlock();
		return NULL;
	}
	dirent_t * ret = opened_dir->cur_dirrent;
	fpath_node_t * cur_node = LIST_ENTRY(opened_dir->position,fpath_node_t, sibling);
	ret->type = cur_node->inode->type;
	ret->file_path = cur_node->file_path;
	tmpfs_unlock();
	return ret;
}

void tmpfs_closedir(dir_t * dir) {
	tmpfs_lock();
	if(dir->cur_dirrent != NULL) {
		free(dir->cur_dirrent);
	}
	tmpfs_close(dir->fd);
	free(dir);
	tmpfs_unlock();
}

static int path_comparator(void * left, void * right) {
	return strcmp(left, right);
}

void tmpfs_mount() {
	fpaths_avl = avl_tree_create(path_comparator);
	fdtable_init();
	add_link("/", inode_new_dir(NULL));
}
