/*
 * print.h
 *
 *  Created on: Feb 23, 2016
 *      Author: sanya1
 */

#ifndef SRC_PRINT_H_
#define SRC_PRINT_H_

#include <stdarg.h>

int vprintf(const char *format, va_list args);
int printf(const char *format, ...);
int vsprintf(char *s, const char *format, va_list args);
int sprintf(char *s, const char *format, ...);



#endif /* SRC_PRINT_H_ */
