/* _GET_LONG_TEST_C_
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

#include <stdio.h>
#include <inttypes.h>
#include "xbrtime.h"

#define TEST_SIZE 16

int main( int argc, char **argv ){
  int mype, npes;
  long *dest = malloc( sizeof(long) * TEST_SIZE );

  xbrtime_init();
  mype = xbrtime_mype();

  // Symmetric memory allocation
  long *source = (long *)(xbrtime_malloc( sizeof(long) * TEST_SIZE ));

  // Initialize the source and dest array
  for( int i=0; i<TEST_SIZE; i++ ){
    source[i] = 0xdeadbeef;
    dest[i] = 0;
  }

  /* perform a barrier */
  xbrtime_barrier_all();

  if( xbrtime_mype() == 0 ){
    /* perform an operation */
    xbrtime_long_get(dest, source, TEST_SIZE, 1);
  }

  // Validate the results
  if( xbrtime_mype() == 0 ){
    for( int i=0; i<TEST_SIZE; i++ ){
      if( dest[i] != 0xdeadbeef ){
        printf("Error detected in get_long_test: dest[%d]=%x", i, dest[i]);
      }
    }
  }
  xbrtime_free( source );
  xbrtime_close();
  free( dest );
  
  return 0;
}

/* EOF */
