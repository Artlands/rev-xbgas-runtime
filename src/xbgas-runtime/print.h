// See LICENSE for license details.
#ifndef _PRINT_H_
#define _PRINT_H_

#undef strcmp

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <limits.h>
#include "syscalls.h"

void printstr(const char* s);
int putchar(int ch);
void printhex(uint64_t x);
int printf(const char* fmt, ...);
int sprintf(char* str, const char* fmt, ...);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _PRINT_H_ */