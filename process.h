
#ifndef SRC_PROCESS_H_
#define SRC_PROCESS_H_

#include "list.h"
#include "paging.h"
#include "threads.h"
#include "elf.h"

typedef enum {
	US_STACK,
	US_CODE
} mm_entry_type;

typedef struct {
	paging_map_region region;
	mm_entry_type type;
	struct list_head list;
}p_mm_entry;

typedef struct{
	struct list_head user_mm_list_head;
	void * user_stack;
	virt_t user_stack_low_begin;
	struct list_head threads_list;
	virt_t user_entry;
	pte_t * pt;
}process;

p_mm_entry * create_p_mm_entry(virt_t user_virt, phys_t paddr, size_t size, mm_entry_type type);
void destroy_p_mm_entry(p_mm_entry * entry);

process * process_current();
void process_assign_thread(process * proc, thread_t * thread);
void process_remove_thread(thread_t * thread);
void process_switch(process * old_process, process * next_process);
void process_jump_user();
void process_set_user_image(process * proc, elf_contents * contents);
process * process_create();

int process_fork();
void process_destroy(process * proc);


#endif /* SRC_PROCESS_H_ */
