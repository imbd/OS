#include "lock.h"
#include "utils.h"
#include "allocator.h"

#ifdef TICKET_LOCK
#include "interrupt.h"
#include <stddef.h>
#include <stdint.h>
#include "memory.h"
#include "print.h"

void * lock_create(int global) {
	ticket_lock * lock = (ticket_lock *)malloc(sizeof(ticket_lock));
	lock->ticket = 0;
	lock->users = 0;
	lock->global = global;
	lock->was_interrupts_enabled = false;
	return lock;
}

void lock_destroy(void *lock) {
	free(lock);
}

void lock_set_global(void * arg_lock) {
	((ticket_lock *)arg_lock)->global = 1;
}

void lock(void * arg_lock) {
	if(arg_lock == NULL ){
		return;
	}
	ticket_lock * lock = (ticket_lock *)arg_lock;
	const uint16_t ticket = __sync_fetch_and_add(&lock->users, 1);
	while(lock->ticket != ticket) {
		barrier();
	}
	__sync_bool_compare_and_swap(&lock->was_interrupts_enabled, true, false);
	if(lock->global && flags_if()){
		lock->was_interrupts_enabled = true;
		cli();
	}
	__sync_synchronize();
}

void unlock(void * arg_lock) {
	if(arg_lock == NULL ){
			return;
	}
	ticket_lock * lock = (ticket_lock *)arg_lock;
	if(lock->global && __sync_bool_compare_and_swap(&lock->was_interrupts_enabled, true, false)) {
		sti();
	}
	__sync_synchronize();
	__sync_add_and_fetch(&lock->ticket, 1);
}

#endif
