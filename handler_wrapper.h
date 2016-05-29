#ifndef HANDLER_WRAPPER_H_
#define HANDLER_WRAPPER_H_
#include "utils.h"

#define PUSHED_REG_NUM 13 /* regs_without sys arguments + rbp inside */
#define PUSHED_SUMMARY (PUSHED_REG_NUM * 8)

#define WRAP(name) name ## _wrapper

#define PUSH_STACK_FRAME \
   push %rbp; \
   mov %rsp, %rbp ;\

#define POP_STACK_FRAME \
   pop %rbp ;\

#define PUSH_ALL_WITHOUT_ARG \
	pushq %rcx ;\
	pushq %rdx ;\
	pushq %rsi ;\
	pushq %rdi ;\
	pushq %r8 ;\
	pushq %r9 ;\
	pushq %r10 ;\
	pushq %r11 ;\
	pushq %r12 ;\
	pushq %r13 ;\
	pushq %r14 ;\
	pushq %r15 ;\

#define PUSH_ARG \
	push %rax ;\
	push %rbx ;\

#define PUSH_ALL \
	PUSH_ARG; \
	PUSH_ALL_WITHOUT_ARG ;\

#define POP_ALL_WITHOUT_ARG \
	popq %r15 ;\
	popq %r14 ;\
	popq %r13 ;\
	popq %r12 ;\
	popq %r11 ;\
	popq %r10 ;\
	popq %r9 ;\
	popq %r8 ;\
	popq %rdi ;\
	popq %rsi ;\
	popq %rdx ;\
	popq %rcx ;\

#define POP_ARG \
	pop %rbx ;\
	pop %rax ;\

#define POP_ALL \
	POP_ALL_WITHOUT_ARG;\
	POP_ARG; \

#define ASM_WRAPPER(name) \
	__asm__  ( \
		EXPAND(WRAP(name))": \n" \
		EXPAND(PUSH_STACK_FRAME) \
		EXPAND(PUSH_ALL) \
		"call " #name ";" \
		EXPAND(POP_ALL) \
		EXPAND(POP_STACK_FRAME) \
		"iretq")

#define ER_ASM_WRAPPER(name) \
	__asm__  ( \
		EXPAND(WRAP(name))": \n" \
		"add $8, %rsp;" \
		EXPAND(PUSH_STACK_FRAME) \
		EXPAND(PUSH_ALL) \
		"call " #name ";" \
		EXPAND(POP_ALL) \
		EXPAND(POP_STACK_FRAME) \
		"iretq")

#define SYSCALL_ASM_WRAPPER(name) \
	__asm__  ( \
		EXPAND(WRAP(name))": \n" \
		EXPAND(PUSH_STACK_FRAME) \
		EXPAND(PUSH_ALL_WITHOUT_ARG) \
		"mov %rsp, %rdi;" \
		"add $"EXPAND(PUSHED_SUMMARY)", %rdi;" \
		EXPAND(PUSH_ARG) \
		"call thread_remember_tss;" \
		EXPAND(POP_ARG) \
		"call " #name ";" \
		EXPAND(POP_ALL_WITHOUT_ARG) \
		EXPAND(POP_STACK_FRAME) \
		"iretq")

#define DO_WRAP(name) \
	VOID_FUNC(WRAP(name)); \
	ASM_WRAPPER(name); \
	VOID_FUNC(name)

#define ER_DO_WRAP(name) \
	VOID_FUNC(WRAP(name)); \
	ER_ASM_WRAPPER(name); \
	VOID_FUNC(name)

#define SYSCALL_DO_WRAP(name) \
	VOID_FUNC(WRAP(name)); \
	SYSCALL_ASM_WRAPPER(name); \
	VOID_FUNC(name)

#endif /* HANDLER_WRAPPER_H_ */
