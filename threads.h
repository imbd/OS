#ifndef SRC_THREADS_H_
#define SRC_THREADS_H_

#include "list.h"
#include <stdint.h>
#include "syscall_def.h"

typedef enum {
	READY_TO_START,
	RUNNING,
	SLEEPING,
	TERMINATED
} thread_status;

typedef struct {
	void * stack;
	void * (*entry)(void *) ;
	void * result;
	void * arg;
	thread_status status;
	uint8_t priority;
	struct list_head list;
	void * proc;
	struct list_head proc_list;
	pid_t tid;
	void * orig_stack;
	void * tss_ptr;
}thread_t;

typedef struct {
	thread_t * owner;
	struct list_head sleeping_threads;
}thread_mutex;

typedef struct {
	struct list_head sleeping_threads;
}thread_cond;

void thread_manager_init(int32_t queues_num);
void thread_manager_callback(float delta_time);

thread_t * thread_create(void * (*entry)(void *) , void * arg) ;
thread_t * thread_create_cpy(void * (*entry)(void *) , void * arg, void *proc);
void thread_create_cpy_ready(thread_t * thread);
void thread_destroy(thread_t * thread);
void thread_yield();
void thread_exit();
void thread_cancel(thread_t * thread);
void thread_join(thread_t * thread);
thread_t * thread_current();
void thread_remember_tss(void * addr);

thread_mutex * thread_mutex_create();
void thread_mutex_destroy(thread_mutex * mutex);
void thread_mutex_lock(thread_mutex * mutex);
void thread_mutex_unlock(thread_mutex * mutex);


thread_cond * thread_cond_create();
void thread_cond_destroy(thread_cond *);
void thread_cond_wait(thread_cond * cond, thread_mutex * mutex);
void thread_cond_signal(thread_cond * cond);
void thread_cond_broadcast(thread_cond * cond);


#endif /* SRC_THREADS_H_ */
