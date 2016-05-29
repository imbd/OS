#include "handler_wrapper.h"

.code64
.section .text
.globl switch_context, jump_userspace, restore_kernel_regs, jump_userspace_fork

switch_context:
	push   %rbp
	mov    %rsp,%rbp
	sub    $0x10,%rsp
	mov    %rdi,-0x8(%rbp)
	mov    %rsi,-0x10(%rbp)
	mov    -0x10(%rbp),%rax
	mov    (%rax),%rax
	test   %rax,%rax
	je     switch_context_load
	pushq %rbp
	pushq %rbx
	pushq %r12
	pushq %r13
	pushq %r14
	pushq %r15
switch_context_load:
	mov    -0x10(%rbp),%rax
	mov    (%rax),%rax
	mov    %rsp,%rdx
	mov    %rdx,(%rax)

	mov    -0x8(%rbp),%rax
	mov    (%rax),%rax
	mov    %rax, %rsp

	mov    -0x10(%rbp),%rax
	mov    -0x8(%rbp),%rdx
	mov    %rdx,(%rax)

	mov    -0x10(%rbp),%rax
	mov    (%rax),%rax
	mov    %rax, %rdi

	mov    -0x10(%rbp),%rax
	mov    (%rax),%rax
	mov    -0x8(%rbp),%rdx
	mov    %rdx,%rsi
	mov    %rax,%rdi
	callq try_wrapper_entry
    popq %r15
	popq %r14
	popq %r13
	popq %r12
	popq %rbx
	popq %rbp
	leaveq
	retq

jump_userspace_fork:
	mov %rdi, %rsp
	POP_ALL_WITHOUT_ARG
	pop %rbp
	mov    %rsp, %rdi
	callq  thread_remember_tss;
	mov $0, %rax
	iretq

jump_userspace:
	pushq  0x20(%rdi)
	pushq  0x18(%rdi)
	pushq  0x10(%rdi)
	pushq  0x8(%rdi)
	pushq  (%rdi)
	mov    %rsp, %rdi
	callq  tss_write_kernel_rsp;
	iretq

