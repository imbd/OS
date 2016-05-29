#ifndef SRC_SYSCALL_H_
#define SRC_SYSCALL_H_

#include "syscall_def.h"

int sys_exec(const char * path);
int sys_write(void * param);
int sys_fork();
int sys_err();
void syscall_init_handler();


#endif /* SRC_SYSCALL_H_ */
