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
#include "test.h"

static thread_mutex * mutex;
static thread_cond *  cond;
static volatile int stageA = 0;
static volatile int stageB = 0;
static volatile int resultA = 0;
static volatile int resultB = 0;

/* A = (10+2)*3
 * B = 4*(5+6)
 * result = A + B = 80
 * */

static void * thread1(void * arg){
	thread_mutex_lock(mutex);
	resultA = 10;
	stageA = 1;
	thread_cond_broadcast(cond);
	while(stageB != 2) {
		thread_cond_wait(cond, mutex);
	}
	resultB *= 4;
	thread_mutex_unlock(mutex);
	return arg;
}

static void * thread2(void *arg){
	thread_mutex_lock(mutex);
	while(stageA != 1){
		thread_cond_wait(cond, mutex);
	}
	resultA += 2;
	stageA = 2;
	thread_cond_broadcast(cond);
	while(stageB != 1) {
		thread_cond_wait(cond, mutex);
	}
	resultB += 5;
	stageB = 2;
	thread_cond_broadcast(cond);
	thread_mutex_unlock(mutex);
	return arg;
}

static void * thread3(void *arg){
	thread_mutex_lock(mutex);
	while(stageA != 2){
		thread_cond_wait(cond, mutex);
	}
	resultA *= 3;
	resultB = 6;
	stageB = 1;
	thread_cond_broadcast(cond);
	thread_mutex_unlock(mutex);
	return arg;
}

static void check(){
	test_assert((resultA + resultB)==80);
	test_pass("test_threads");
}


void *start_thread(void * arg){
	mutex = thread_mutex_create();
	cond  = thread_cond_create();
	thread_t * t2 = thread_create(thread2, NULL);
	thread_t * t1 = thread_create(thread1, NULL);
	thread_t * t3 = thread_create(thread3, NULL);
	thread_join(t1);
	thread_join(t2);
	thread_join(t3);
	check();
	thread_destroy(t1);
	thread_destroy(t2);
	thread_destroy(t3);
	thread_cond_destroy(cond);
	thread_mutex_destroy(mutex);
	return arg;
}

void test_threads() {
	thread_create(start_thread, NULL);
}
