#define __ASSEMBLY__
#include "syscall_def.h"

.code64
.section .text
.globl syscall_handler, syscall

syscall_handler:
	push   %rbp
   	mov    %rsp,%rbp
	sub    $0x20,%rsp
	mov    %rax,-0x8(%rbp)
	mov    %rbx,-0x10(%rbp)
	mov    -0x10(%rbp),%rax
	mov    -0x8(%rbp),%rdx
	mov    %rax,%rsi
	mov    %edx,%edi
	callq  syscall_dispatcher
	cltq
	mov    %rax,-0x18(%rbp)
	mov    -0x18(%rbp),%rax
	leaveq
	retq

syscall:
	push   %rbp
	mov    %rsp,%rbp
	push   %rbx
	sub    $0x20,%rsp
	mov    %rdi,-0x20(%rbp)
	mov    %rsi,-0x28(%rbp)
	mov    -0x20(%rbp),%rax
	mov    -0x28(%rbp),%rbx
	int    $SYSCALL_INTERRUPT_NUMB
	mov    %rax,-0x10(%rbp)
	mov    -0x10(%rbp),%rax
	add    $0x20,%rsp
	pop    %rbx
	pop    %rbp
	retq


