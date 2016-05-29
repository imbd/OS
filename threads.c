#include "threads.h"
#include "allocator.h"
#include <stddef.h>
#include "utils.h"
#include "lock.h"
#include "memory.h"
#include "print.h"
#include "tmpfs.h"
#include "process.h"
#include "strings.h"
#include "tss.h"


#define THREAD_STACK_START_SIZE 8192

#define DEFAULT_PRIORITY_NUM 20

static thread_t * volatile current_thread;
struct list_head * volatile  queues;
static size_t volatile queues_num;

struct  list_head * volatile terminated_threads;
static void * volatile terminated_threads_lock;

static const float quant_diff_q = 0.01;
static float volatile current_thread_working_elapsed_time = 0;

static thread_t * volatile current_thread = NULL;
static thread_t * volatile main_thread ;
static thread_t * volatile cleaner_thread;

static void * volatile threads_lock;

static volatile pid_t last_tid = 1;

void thread_cancel(thread_t * thread) {
	lock(threads_lock);
	if(thread->status != TERMINATED) {
		process_remove_thread(thread);
		thread->status = TERMINATED;
		list_del(&thread->list);

		lock(terminated_threads_lock);
		list_add(&thread->list, terminated_threads);
		unlock(terminated_threads_lock);
	}

	unlock(threads_lock);
}
void thread_exit() {
	thread_cancel(current_thread);
	thread_yield();
}

static void * cleaner_body(void * arg) {
	while(1) {
		thread_t * freeing_stack_thread = NULL;
		lock(terminated_threads_lock);
		if(!list_empty(terminated_threads)){
			freeing_stack_thread = LIST_ENTRY(list_first(terminated_threads), thread_t, list);
			list_del(&freeing_stack_thread->list);
		}
		if(freeing_stack_thread) {
			free(freeing_stack_thread->stack);
			freeing_stack_thread->stack = NULL;
		}
		unlock(terminated_threads_lock);
		thread_yield();
	}
	return arg;
}

static void create_main_thread() {
	main_thread = malloc(sizeof(thread_t));
	main_thread->status = RUNNING;
	main_thread->priority = queues_num - 1;
	main_thread->tid = last_tid++;
	main_thread->stack = main_thread->orig_stack = get_rsp();
	list_init(&main_thread->list);
	list_init(&main_thread->proc_list);
	list_add_tail(&main_thread->list, &queues[main_thread->priority]);
}

static void create_cleaner_thread() {
	cleaner_thread = thread_create(cleaner_body, NULL);
	cleaner_thread->priority = queues_num - 1;
	list_del(&cleaner_thread->list);
	list_add_tail(&main_thread->list, &queues[main_thread->priority]);
}

static void create_helper_threads() {
	create_main_thread();
	create_cleaner_thread();
	process_assign_thread(process_create(), main_thread);
	process_assign_thread(process_create(), cleaner_thread);
	current_thread = main_thread;
}

void thread_manager_init(int32_t queues_num_arg) {
	if(queues_num_arg == -1){
		queues_num_arg = DEFAULT_PRIORITY_NUM;
	}
	queues_num = queues_num_arg;
	queues = malloc(queues_num * sizeof(struct list_head));
	for(size_t i = 0; i < queues_num; i++) {
		list_init(&queues[i]);
	}
	terminated_threads = malloc(sizeof(struct list_head));
	list_init(terminated_threads);
	terminated_threads_lock = lock_create(0);

	threads_lock = lock_create(0); /* it's global but not here */
	create_helper_threads();
	lock_set_global(threads_lock); /* but here */
	allocator_set_sync();
	tmpfs_set_sync();
}

static thread_t * thread_allocate() {
	thread_t * thread = malloc(sizeof(thread_t));
	thread->tss_ptr = thread->orig_stack = thread->stack =
			(void *)((virt_t)malloc(THREAD_STACK_START_SIZE) + THREAD_STACK_START_SIZE - 1);
	return thread;
}

thread_t * thread_create(void * (*entry)(void *) , void * arg) {
	thread_t * thread = thread_create_cpy(entry, arg, process_current());
	thread_create_cpy_ready(thread);
	return thread;
}

thread_t * thread_create_cpy(void * (*entry)(void *) , void * arg, void * proc) {
	lock(threads_lock);
	thread_t * thread = thread_allocate();

	thread->arg = arg;
	thread->entry = entry;
	thread->result = NULL;
	thread->status = READY_TO_START;
	thread->priority = 0;
	thread->tid = last_tid++;
	list_init(&thread->proc_list);
	list_init(&thread->list);

	if (proc != NULL) {
		process_assign_thread(proc, thread);
	}

	unlock(threads_lock);
	return thread;
}

void thread_create_cpy_ready(thread_t * thread) {
	lock(threads_lock);
	list_add_tail(&thread->list, &queues[thread->priority]);
	unlock(threads_lock);
}

void try_wrapper_entry(thread_t * old_thread, thread_t * thread){
	process_switch(old_thread->proc, thread->proc);
	tss_write_kernel_rsp(thread->tss_ptr);
	if(thread->status == READY_TO_START) {
		thread->status = RUNNING;
		unlock(threads_lock);

		thread->result = thread->entry(thread->arg);
		thread_exit(thread);
	}
}

void switch_context(thread_t * new_thread, thread_t *volatile* old_thread) ;

static void thread_move_up_priority(thread_t * thread) {
	if(thread->priority < queues_num - 1){
		list_del(&thread->list);
		thread->priority++;
		list_add_tail(&thread->list, &queues[thread->priority]);
	}
}

static void thread_down_up_priority(thread_t * thread) {
	if(thread->priority > 0) {
		list_del(&thread->list);
		thread->priority--;
		list_add_tail(&thread->list, &queues[thread->priority]);
	}
}

static void thread_manage_switch() {
	for(size_t i = 0; i < queues_num; i++) {
		if(!list_empty(&queues[i])) {
			thread_t * thread = LIST_ENTRY(list_first(&queues[i]), thread_t, list);
			list_del(&thread->list);
			list_add_tail(&thread->list, &queues[i]);
			current_thread_working_elapsed_time = quant_diff_q * (i + 1);
			switch_context(thread, &current_thread);
			return;
		}
	}
}

void thread_yield() {
	lock(threads_lock);
	if(current_thread != NULL && current_thread->status == RUNNING) {
		if(current_thread_working_elapsed_time <= 0) {
			thread_down_up_priority(current_thread);
		} else {
			thread_move_up_priority(current_thread);
		}
	}
	thread_manage_switch();
	unlock(threads_lock);
}

void thread_manager_callback(float delta_time) {
	lock(threads_lock);
	current_thread_working_elapsed_time -= delta_time;
	if(current_thread_working_elapsed_time <= 0 || current_thread->status == TERMINATED) {
		unlock(threads_lock);
		thread_yield();
	} else {
		unlock(threads_lock);
	}
}

void thread_destroy(thread_t * thread) {
	lock(threads_lock);
	lock(terminated_threads_lock);
	list_del(&thread->list);
	if(thread->stack) {
		free(thread->stack);
	}
	free(thread);
	unlock(terminated_threads_lock);
	unlock(threads_lock);
}

void thread_join(thread_t * thread) {
	bool is_terminated = false;
	while(!is_terminated){
		lock(threads_lock);
		is_terminated = thread->status == TERMINATED;
		unlock(threads_lock);
		thread_yield();
	}
}

thread_mutex * thread_mutex_create(){
	thread_mutex * mutex = malloc(sizeof(thread_mutex));
	mutex->owner = NULL;
	list_init(&mutex->sleeping_threads);
	return mutex;
}

void thread_mutex_destroy(thread_mutex * mutex){
	free(mutex);
}

static void thread_move_to_sleep(thread_t * thread) {
	list_del(&thread->list);
	thread->status = SLEEPING;
}

static void thread_wakeup(thread_t *thread) {
	list_add_tail(&thread->list, &queues[thread->priority]);
	thread->status = RUNNING;
}

void thread_mutex_lock(thread_mutex * mutex) {
	lock(threads_lock);
	if(mutex->owner == NULL || mutex->owner == current_thread){
		mutex->owner = current_thread;
		unlock(threads_lock);
	} else {
		thread_move_to_sleep(current_thread);
		list_add(&current_thread->list, &mutex->sleeping_threads);
		unlock(threads_lock);
		thread_yield();
	}
}

void thread_mutex_unlock(thread_mutex * mutex) {
	lock(threads_lock);
	if(mutex->owner == current_thread) {
		thread_t * new_owner = NULL;
		if(!list_empty(&mutex->sleeping_threads)){
			new_owner = LIST_ENTRY(list_first(&mutex->sleeping_threads), thread_t, list);
			list_del(&new_owner->list);
			thread_wakeup(new_owner);
		}
		mutex->owner = new_owner;
	}
	unlock(threads_lock);
}

thread_cond * thread_cond_create(){
	thread_cond * cond = malloc(sizeof(thread_cond));
	list_init(&cond->sleeping_threads);
	return cond;
}

void thread_cond_destroy(thread_cond * cond) {
	free(cond);
}

void thread_cond_wait(thread_cond * cond, thread_mutex * mutex){
	lock(threads_lock);
	thread_move_to_sleep(current_thread);
	list_add(&current_thread->list, &cond->sleeping_threads);
	unlock(threads_lock);
	thread_mutex_unlock(mutex);

	thread_yield();
	thread_mutex_lock(mutex);
}

void thread_cond_signal(thread_cond * cond) {
	lock(threads_lock);
	if(!list_empty(&cond->sleeping_threads)){
		thread_t * thread = LIST_ENTRY(list_first(&cond->sleeping_threads), thread_t, list);
		list_del(&thread->list);
		thread_wakeup(thread);
	}
	unlock(threads_lock);
}
void thread_cond_broadcast(thread_cond * cond) {
	lock(threads_lock);
	while (!list_empty(&cond->sleeping_threads)){
		thread_t * thread = LIST_ENTRY(list_first(&cond->sleeping_threads), thread_t, list);
		list_del(&thread->list);
		thread_wakeup(thread);
	}
	unlock(threads_lock);
}

thread_t * thread_current() {
	return current_thread;
}

void thread_remember_tss(void *addr) {
	current_thread->tss_ptr = addr;
	tss_write_kernel_rsp(addr);
}
