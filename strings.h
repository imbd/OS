#ifndef STRINGS_H_
#define STRINGS_H_

#include <stddef.h>
void memcpy(void * desc_arg, const void * src_arg, size_t size);
size_t strlen(const char * s);
int strcmp(const char * left, const char * right);
int strncmp(const char * left, const char * right, size_t len);
int str_find_last(const char * str, char c, int limit);
char * str_cpy(const char * str);
void memset(void * desc_arg, char value, size_t size);

#endif /* STRINGS_H_ */
