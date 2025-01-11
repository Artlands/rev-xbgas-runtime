/* _ALLOC_TEST_1_C_
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
  void *ptr1, *ptr2, *ptr3;
  size_t sz1 = 2048, sz2 = 1984, sz3 = 1024;

  printf( "Allocating %d bytes\n", (int)(sz1) );
  ptr1 = malloc( sz1 );
  printf( "PTR 1 = %p\n", ptr1 );

  printf( "Allocating %d bytes\n", (int)(sz2) );
  ptr2 = malloc( sz2 );
  printf( "PTR 2 = %p\n", ptr2 );

  free( ptr1 );
  free( ptr2 );

  printf( "Allocating %d bytes\n", (int)(sz3) );
  ptr3 = malloc( sz3 );
  printf( "PTR 3 = %p\n", ptr3 );
  free( ptr3 );

  return rtn;
}

/* EOF */
