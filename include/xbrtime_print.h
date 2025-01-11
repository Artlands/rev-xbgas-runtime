// See LICENSE for license details.

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
