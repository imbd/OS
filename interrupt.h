#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include <stdint.h>

#define PIC_BOUND_MASTER 0x20
#define PIC_BOUND_SLAVE 0x28

#define IDT_SIZE 0x100
#define INTGATE_TYPE 0x8E
#define TRAPGATE_TYPE 0xEF

#define N_RESERVED_INTERRUPTS_GATES 0x20

struct idt_ptr {
	uint16_t size;
	uint64_t base;
}__attribute__((packed));
typedef struct idt_ptr idt_ptr_t;

struct idt_entry {
	uint16_t offset_1;
	uint16_t selector;
	uint8_t zero;
	uint8_t type_attr;
	uint16_t offset_2;
	uint32_t offset_3;
	uint32_t reserved;
}__attribute__((packed));
typedef struct idt_entry idt_entry_t;

static inline void set_idt(const idt_ptr_t *ptr) {
	__asm__ volatile ("lidt (%0)" : : "a"(ptr));
}

static inline void sti() {
	__asm__ volatile ("sti");
}

static inline void cli() {
	__asm__ volatile ("cli");
}

static inline void cld() {
	__asm__ volatile ("cld");
}


void idt_setup();
void idt_set_gate(uint8_t id, uint64_t adress, uint16_t selector, uint8_t type);
void idt_set_gate_dpl(uint8_t id, uint64_t adress, uint16_t selector, uint8_t type, int dpl);

#endif /*__INTERRUPT_H__*/
