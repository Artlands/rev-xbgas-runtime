/* _MALLOC_TEST_3_C_
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

#include "xbrtime.h"

#define _XBGAS_ALLOC_SIZE_ 1024

int main( int argc, char **argv ){
  int rtn = 0;
  void *ptr1 = NULL, *ptr2 = NULL;
  size_t size = _XBGAS_ALLOC_SIZE_;

  rtn = xbrtime_init();

  printf( "Allocating %d bytes on symmetric heaps\n", (int)(size) );
  ptr1 = xbrtime_malloc( size );
  ptr2 = xbrtime_malloc( size * 2);

  printf( "PTR = %p\n", ptr1 );
  printf( "PTR = %p\n", ptr2 );

  printf( "Freeing the memory\n" );
  xbrtime_free( ptr1 );
  xbrtime_free( ptr2 );

  xbrtime_close();
  return rtn;
}

/* EOF */
