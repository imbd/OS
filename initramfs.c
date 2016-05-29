#include "initramfs.h"
#include "utils.h"
#include <stddef.h>
#include <stdbool.h>
#include "multiboot.h"
#include "allocator.h"
#include "memory.h"
#include "mmap.h"
#include "strings.h"
#include "tmpfs.h"
#include "print.h"

extern const uint32_t mboot_info ;

#define MBOOT_FLAG_MODS BIT(3)

#define CPIO_MAGIC "070701"

static void * initramfs_addr = NULL;
static size_t initframs_size = 0;

static void initramfs_find_addr() {
	multiboot_info_t *mbi = (multiboot_info_t *) (uint64_t)mboot_info;
	if(!CHECK_FLAG(mbi->flags, MBOOT_FLAG_MODS)) {
		return;
	}
	multiboot_module_t * mod = (multiboot_module_t * ) (uint64_t)mbi->mods_addr;
	for(uint32_t i = 0; i < mbi->mods_count; i++, mod++) {
		size_t size = mod->mod_end - mod->mod_start + 1;
		if(size >= sizeof(struct cpio_header)){
			struct cpio_header * header = (struct cpio_header *)(get_aligned_addr((virt_t)mod->mod_start, 4));
			if(!strncmp(CPIO_MAGIC, header->magic, sizeof(header->magic))) {
				initramfs_addr = va((uint64_t)mod->mod_start);
				initframs_size = size;
				return;
			}
		}
	}
}

void initramfs_init() {
	initramfs_find_addr();
	if ( initramfs_addr != NULL) {
		mmap_reserve_subblock((void *)pa(initramfs_addr), initframs_size);
	}
}

static void inc(uint64_t delta) {
	initframs_size -= delta;
	initramfs_addr = (void *)((virt_t) initramfs_addr + delta);
}

static void align() {
	inc(get_aligned_addr((virt_t)initramfs_addr, 4) - (virt_t)initramfs_addr);
}

static int convert(char ptr[]){
	int ret = 0;
	for(size_t i = 0; i < 8; i++){
		ret *= 16;
		if(ptr[i] - '0' < 10)
			ret +=  ptr[i] - '0';
		else
			ret += ptr[i] - 'A'+ 10;
	}
	return ret;
}

static char * make_reg_path(const char * old) {
	char * new = malloc(strlen(old) + 2);
	memcpy(new + 1, old, strlen(old) + 1);
	new[0] = '/';
	return new;
}

static char * make_dir_path(const char * old) {
	char * new = malloc(strlen(old) + 3);
	memcpy(new + 1, old, strlen(old));
	new[0] = '/';
	new[strlen(old) + 1] = '/';
	new[strlen(old) + 2] = '\0';
	return new;
}

void initramfs_read_contents_push_to_tmpfs() {
	while(1) {
		align();

		if(initframs_size < sizeof(struct cpio_header)) {
			break;
		}
		struct cpio_header * header = initramfs_addr;
		inc(sizeof(struct cpio_header));
		const size_t name_size = convert(header->namesize);
		char * path = initramfs_addr;
		if(strcmp(path, END_OF_ARCHIVE) == 0){
			break;
		}

		inc(name_size);
		align();

		void * buf = initramfs_addr;

		inc(convert(header->filesize));

		if(S_ISDIR(convert(header->mode))){
			char * dir_path = make_dir_path(path);
			tmpfs_mkdir(dir_path);
			free(dir_path);
		} else {
			char * reg_path = make_reg_path(path);
			tmpfs_create(reg_path);
			int fd = tmpfs_open(reg_path, OP_WRITE);
			tmpfs_write(fd, buf, convert(header->filesize));
			tmpfs_close(fd);
			free(reg_path);
		}
	}
}
