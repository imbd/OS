#include "syscall_user.h"
#include "utils.h"
#include "strings.h"
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>

int sprintf(char *s, const char *format, ...);

int64_t syscall(uint64_t param, void * data);

#define BUF_SIZE 100
char s[BUF_SIZE];

int uprintf(const char * format, ...) {
	va_list args;
	va_start(args, format);
	memset(s, 0, BUF_SIZE);
	sprintf(s, format, args);
	va_end(args);
	return syscall(0, s);
}

int fork(uint64_t *param) {
	int64_t ret = syscall(1, NULL);
	if(ret == SYSCALL_WRONG_ARG)
		return -1;
	*param = ret;
	return 0;
}



