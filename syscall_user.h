#ifndef SRC_SYSCALL_USER_H_
#define SRC_SYSCALL_USER_H_

#include "syscall_def.h"
#include <stdint.h>

int64_t syscall(uint64_t param, void * data);
int uprintf(const char * format, ...);
int fork(uint64_t *param);


#endif /* SRC_SYSCALL_USER_H_ */
