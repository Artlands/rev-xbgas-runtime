/* _ALLOC_TEST_2_C_
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
  size_t sz = _XBGAS_ALLOC_SIZE_;

  rtn = xbrtime_init();

  printf( "Allocating %d bytes on symmetric heaps", (int)(sz) );
  ptr = xbrtime_malloc( sz );

  printf( "PTR = %p", ptr );

  printf( "Reallocating %d bytes on symmetric heaps", (int)(sz*2) );
  ptr = xbrtime_realloc( ptr, sz*2 );

  printf( "After reallocating, PTR = %p", ptr );

  printf( "Freeing the memory" );
  xbrtime_free( ptr );

  xbrtime_close();
  return rtn;
}

/* EOF */
