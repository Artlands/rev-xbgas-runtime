/* _ALIGN_TEST_1_C_
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

#define _XBGAS_ALLOC_SIZE_ 483

int main( int argc, char **argv ){
  int rtn = 0;
  void *ptr = NULL;
  size_t size = _XBGAS_ALLOC_SIZE_;

  rtn = xbrtime_init();

  printf( "Allocating %d bytes on symmetric heaps", (int)(size) );
  ptr = xbrtime_align( sizeof( int ), size );

  printf( "PTR = %p", ptr );

  // Check if ptr is aligned to sizeof( uint64_t )
  if( ptr && ( (uintptr_t)ptr % sizeof( int ) ) == 0 ){
    printf( "PTR is aligned to sizeof( int )" );
  }

  printf( "Freeing the memory" );
  xbrtime_free( ptr );

  xbrtime_close();
  return rtn;
}

/* EOF */
