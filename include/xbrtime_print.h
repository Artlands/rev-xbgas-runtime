/*
 * _XBRTIME_PRINT_H_
 *
 * Copyright (C) 2017-2025 Tactical Computing Laboratories, LLC
 * All Rights Reserved
 * contact@tactcomplabs.com
 *
 * This file is a part of the XBGAS-RUNTIME package.  For license
 * information, see the LICENSE file in the top level directory
 * of the distribution.
 *
 */

#ifndef _XBRTIME_PRINT_H_
#define _XBRTIME_PRINT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void printstr( const char* s );
int putchar( int ch );
void printhex( uint64_t x );
int printf( const char* fmt, ... );
int sprintf( char* str, const char* fmt, ... );

#ifdef __cplusplus
}
#endif  /* extern "C" */

#endif  /* _XBRTIME_PRINT_H_ */

/* EOF */
