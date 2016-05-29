#include "interrupt.h"
#include "pic.h"
#include "pit.h"
#include "video.h"
#include "handler_wrapper.h"
#include "uart.h"
#include "print.h"
#include "backtrace.h"
#include "mmap.h"
#include "allocator.h"
#include "paging.h"
#include "buddy_allocator.h"
#include "threads.h"
#include <stddef.h>
#include "tests_list.h"
#include "tmpfs.h"
#include "strings.h"
#include "initramfs.h"
#include "elf.h"
#include "tss.h"
#include "syscall.h"
#include "test.h"

#define INIT_PATH "/initramfs/init"

void readdir_recursive(const char * path){
	printf("listing dir %s\n", path);
	dir_t * dir = tmpfs_opendir(path);
	dirent_t * dirent;
	while((dirent = tmpfs_readdir(dir)) != NULL) {
		printf("%s %d\n", dirent->file_path, (dirent->type == IS_DIR));
		if(dirent->type == IS_DIR) {
			readdir_recursive(dirent->file_path);
		}
	}
	printf("ending listing dir %s\n", path);
 	tmpfs_closedir(dir);
}

void exec_init() {
	sys_exec(INIT_PATH);
}

void main(void)
{
	pic_setup();
	idt_setup();
	pit_setup();
	uart_setup();
	pit_set_thread_manager_vector();
	syscall_init_handler();

	mmap_init();
	initramfs_init();
	allocator_init();

	mmap_print();
	paging_init();
	tss_init();


	tmpfs_mount();
	initramfs_read_contents_push_to_tmpfs();
	readdir_recursive("/");

	thread_manager_init(-1);
	sti();

	test_set_log(printf);

	if(false) {
		test_threads();
	}

	if(false) {
		test_buddy();
		test_slab();
	}

	printf("OK, init completed, running init now\n");
	exec_init();
	while (1);
}
