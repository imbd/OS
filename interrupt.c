#include "interrupt.h"
#include "memory.h"
#include "pic.h"
#include "handler_wrapper.h"
#include "video.h"
#include "print.h"
#include "backtrace.h"

static idt_entry_t idt_entries[IDT_SIZE];
static idt_ptr_t idt_ptr;

void interrupt_handler_wrappers_set_defaults();

void common_handler_er(int num) {
	printf("_------------------------___\n");
	printf("Error %d\n", num);
	printf("_------------------------___\n");
	while(1);
}

void common_handler(int num){
	printf("_------------------------___\n");
	printf("Interrupt %d\n", num);
	printf("_------------------------___\n");
	while(1);
}

void idt_set_gate(uint8_t id, uint64_t adress, uint16_t selector, uint8_t type){
	idt_entries[id].offset_1 = LOW(adress, 16);
	idt_entries[id].offset_2 = SPLICE(adress, 16, 32);
	idt_entries[id].offset_3 = SPLICE(adress, 32, 64);
	idt_entries[id].selector = selector;
	idt_entries[id].zero = 0;
	idt_entries[id].type_attr = type;
}

void idt_set_gate_dpl(uint8_t id, uint64_t adress, uint16_t selector, uint8_t type, int dpl){
	idt_set_gate(id, adress, selector, type);
	idt_entries[id].type_attr = type | (dpl << 5);
}

void idt_setup(){
	idt_ptr.size  = (sizeof (idt_entries)) - 1;
	idt_ptr.base = (uint64_t)&idt_entries;

	interrupt_handler_wrappers_set_defaults();
	set_idt(&idt_ptr);
}
