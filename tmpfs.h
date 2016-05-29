#ifndef SRC_TMPFS_H_
#define SRC_TMPFS_H_

#include <stddef.h>
#include "list.h"

typedef enum {
	IS_DIR,
	IS_REG
}ftype;

typedef enum {
	OP_READ	= 1,
	OP_WRITE = 2
}fopen_type;

typedef struct {
	ftype type;
	const char * file_path;
}dirent_t;

typedef struct {
	int fd;
	struct list_head * position;
	dirent_t * cur_dirrent;
}dir_t;

void tmpfs_set_sync();
void tmpfs_mount();
void tmpfs_create(const char * path);
void tmpfs_link(const char * oldpath, const char * newpath);
void tmpfs_remove(const char * path);
int tmpfs_open(const char * path, int type);
void tmpfs_close(int fd);


void tmpfs_read(int fd, void * buf, size_t count);
void tmpfs_write(int fd, void * buf, size_t count);
void tmpfs_seek(int fd, size_t offset);
size_t tmpfs_get_reading_offset(int fd);

void tmpfs_mkdir(const char * path);
void tmpfs_rmdir(const char * path);
dir_t * tmpfs_opendir(const char * path);
dirent_t * tmpfs_readdir(dir_t * opened_dir);
void tmpfs_closedir(dir_t * opened_dir);



#endif /* SRC_TMPFS_H_ */
