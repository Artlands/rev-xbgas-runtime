/* _REALLOC_TEST_1_C_
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

#include "xbrtime.h"

#define _XBGAS_ALLOC_SIZE_ 16

int main( int argc, char **argv ){
  int rtn = 0;
  void *ptr = NULL;
  size_t size = _XBGAS_ALLOC_SIZE_;

  rtn = xbrtime_init();

  printf( "Allocating %d bytes on symmetric heaps\n", (int)(size) );
  ptr = xbrtime_malloc( size );

  printf( "PTR = %p\n", ptr );

  printf( "Reallocating %d bytes on symmetric heaps\n", (int)(size*2) );
  ptr = xbrtime_realloc( ptr, size*2 );

  printf( "After reallocating, PTR = %p\n", ptr );

  printf( "Freeing the memory\n" );
  xbrtime_free( ptr );

  xbrtime_close();
  return rtn;
}

/* EOF */
