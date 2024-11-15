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

int main( int argc, char **argv ){
  int rtn = 0;
  size_t count = 120;
  size_t size = 64;

  void *ptr = NULL;
  
  rtn = xbrtime_init();

  printf( "Allocating %d bytes on symmetric heaps", (int)(count * size) );
  ptr = xbrtime_calloc( count, size );

  printf( "PTR = %p", ptr );

  printf( "Freeing the memory" );
  xbrtime_free( ptr );

  xbrtime_close();
  return rtn;
}

/* EOF */
