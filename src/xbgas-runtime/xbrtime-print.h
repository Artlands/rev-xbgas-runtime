/*
 * _XBRTIME_PRINT_H_
 *
 * Copyright (C) 2017-2024 Tactical Computing Laboratories, LLC
 * All Rights Reserved
 * contact@tactcomplabs.com
 *
 * This file is a part of the XBGAS-RUNTIME package.  For license
 * information, see the LICENSE file in the top level directory
 * of the distribution.
 *
 */

/*!   \file xbrtime-print.h
      \brief XBGAS Runtime Print Header File

      The XBGAS Runtime provides C/CXX level function interfaces
      for applications to conveniently utilize the shared memory
      capabilities present in the xBGAS extension to the RISC-V
      specification
*/

#ifndef _XBRTIME_PRINT_H_
#define _XBRTIME_PRINT_H_

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

#endif /* _XBRTIME_PRINT_H_ */