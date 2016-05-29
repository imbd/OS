#include "process.h"
#include <stddef.h>
#include "list.h"
#include "allocator.h"
#include "paging.h"
#include "threads.h"
#include "elf.h"
#include "print.h"
#include "tss.h"
#include "strings.h"
#include "handler_wrapper.h"

#define USERSPACE_STACK_DEFAULT_SIZE PAGE_SIZE_2M
#define USERSPACE_HIGH 0x100000000

void jump_userspace(userspace_jumping_args*);
void * jump_userspace_fork(void *);

p_mm_entry * create_p_mm_entry(virt_t user_virt, phys_t paddr, size_t size, mm_entry_type type) {
	p_mm_entry * new_mm_entry = malloc(sizeof(p_mm_entry));
	list_init(&new_mm_entry->list);
	new_mm_entry->region.len = size;
	new_mm_entry->region.phys_start = paddr;
	new_mm_entry->region.virt_start = user_virt;
	new_mm_entry->type = type;
	return new_mm_entry;
}

void destroy_p_mm_entry(p_mm_entry * entry) {
	list_del(&entry->list);
	free(entry);
}

process * process_create() {
	process * ret = malloc(sizeof(process));
	list_init(&ret->user_mm_list_head);
	list_init(&ret->threads_list);
	ret->user_stack = NULL;
	ret->pt = NULL;
	return ret;
}

static void process_create_pt(process * proc) {
	proc->pt = paging_create_newpml_from_process_mm_list(&proc->user_mm_list_head);
}

static void process_create_user_stack(process * proc) {
	proc->user_stack = malloc_aligned(USERSPACE_STACK_DEFAULT_SIZE, PAGE_SIZE_2M);
	proc->user_stack_low_begin = USERSPACE_HIGH;
	virt_t stack_end = proc->user_stack_low_begin - USERSPACE_STACK_DEFAULT_SIZE;

	p_mm_entry * new_mm_entry = create_p_mm_entry(stack_end,
			pa(proc->user_stack),
			USERSPACE_STACK_DEFAULT_SIZE,
			US_STACK);
	list_add(&new_mm_entry->list, &proc->user_mm_list_head);
}

void process_set_user_image(process * proc, elf_contents * contents) {
	proc->user_mm_list_head = contents->mm_list_head;
	proc->user_mm_list_head.next->prev = &proc->user_mm_list_head;
	proc->user_mm_list_head.prev->next = &proc->user_mm_list_head;
	process_create_user_stack(proc);
	process_create_pt(proc);
	proc->user_entry = contents->entry;
	destroy_elf_contents(contents);
}

void process_jump_user() {
	process * current_process = process_current();
	process_switch(current_process, current_process);
	userspace_jumping_args args  = {
		.cs = USER_CODE,
		.rip = current_process->user_entry,
		.flags = FLAGS_IF,
		.rsp = current_process->user_stack_low_begin,
		.ss = USER_DATA
	};
	jump_userspace(&args);
}

void process_destroy(process * proc) {
	while(!list_empty(&proc->user_mm_list_head)) {
		p_mm_entry * entry = LIST_ENTRY(proc->user_mm_list_head.next, p_mm_entry, list);
		destroy_p_mm_entry(entry);
	}
	free(proc->user_stack);
	free(proc);
}

void process_assign_thread(process * proc, thread_t * thread) {
	list_add(&thread->proc_list, &proc->threads_list);
	thread->proc = proc;
}

void process_remove_thread(thread_t * thread) {
	process * proc = thread->proc;
	list_del(&thread->proc_list);
	if (list_empty(&proc->threads_list)) {
		process_destroy(proc);
	}
}

int process_fork() {
	/* We'll copy only current kernel thread responds for process */
	process * current_process = process_current();
	process * new_process = process_create();
	process_create_user_stack(new_process);
	memcpy(new_process->user_stack, current_process->user_stack, USERSPACE_STACK_DEFAULT_SIZE);
	LIST_FOR_EACH(ptr, &(current_process->user_mm_list_head)) {
		p_mm_entry * entry = LIST_ENTRY(ptr, p_mm_entry, list);
		if (entry->type != US_STACK) {
			void * mem = malloc_aligned(entry->region.len, PAGE_SIZE_2M);
			memcpy(mem, va(entry->region.phys_start),entry->region.len);
			list_add(&create_p_mm_entry(entry->region.virt_start, pa(mem), entry->region.len, US_CODE)->list,
						&new_process->user_mm_list_head);
		}
	}
	process_create_pt(new_process);

	userspace_jumping_args * stack_args = (userspace_jumping_args * )tss_read_kernel_rsp();
	thread_t * thread = thread_create_cpy(jump_userspace_fork, NULL, new_process);
	size_t saved_regs_summary = PUSHED_SUMMARY;
	size_t saved_and_jumping_summary = saved_regs_summary + sizeof(userspace_jumping_args);
	thread->stack = (char*)thread->stack - saved_and_jumping_summary;
	memcpy(thread->stack , (char *)stack_args - saved_regs_summary, saved_and_jumping_summary);
	thread->arg = thread->stack;
	thread_create_cpy_ready(thread);
	return thread->tid;
}

void process_switch(process * current_process, process * next_process) {
	(void)(current_process);
	if(next_process->pt != NULL)
		store_pml4(pa(next_process->pt));
}

process * process_current() {
	if (!thread_current())
		return NULL;
	return thread_current() -> proc;
}
