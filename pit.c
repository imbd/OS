#include "pit.h"
#include "utils.h"
#include "ioport.h"
#include "memory.h"
#include "interrupt.h"
#include "pic.h"
#include "video.h"
#include "handler_wrapper.h"
#include "threads.h"
#include "tss.h"
#include "print.h"

DO_WRAP(default_pit_handler){
	pic_eoi(0);
}

static float SUMMARY_FREQ;
static float SUMMARY_DELTA;

#define THREAD_MANAGER_PIT_HANDLER_CALLBACK_DELTA 0.005f


DO_WRAP(thread_manager_pit_handler) {
	static float current_delta = 0;
	current_delta += SUMMARY_DELTA;
	pic_eoi(0);
	if(current_delta >= THREAD_MANAGER_PIT_HANDLER_CALLBACK_DELTA) {
		thread_manager_callback(current_delta);
		current_delta = 0;
	}
}

void pit_replace_vector(uint64_t handler){
	idt_set_gate(PIC_BOUND_MASTER , handler, KERNEL_CODE, INTGATE_TYPE);
}

void pit_setup(){
	SUMMARY_FREQ = PIT_FREQUENCY * 1.0f / PIT_COUNTER;
	SUMMARY_DELTA = 1.0f / SUMMARY_FREQ;

	out8(PIT_CONTROL_PORT, PIT_CONTROL_COMMAND);
	out8(PIT_DATA_PORT_CHANNEL_0, LOW(PIT_COUNTER, 8));
	out8(PIT_DATA_PORT_CHANNEL_0, SPLICE(PIT_COUNTER, 8, 16));
	pit_replace_vector((uint64_t )&WRAP(default_pit_handler));
}


void pit_set_thread_manager_vector() {
	pit_replace_vector((uint64_t)&WRAP(thread_manager_pit_handler));
}
