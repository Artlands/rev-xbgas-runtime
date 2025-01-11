/* _PUT_LONG_TEST_C_
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

#define TEST_SIZE 16

int main( int argc, char **argv ){
  int mype, npes;
  long *source = malloc( sizeof(long) * TEST_SIZE );

  xbrtime_init();
  mype = xbrtime_mype();

  // Symmetric memory allocation
  long *dest = (long *)(xbrtime_malloc( sizeof(long) * TEST_SIZE ));

  // Initialize the source and dest array
  for( int i=0; i<TEST_SIZE; i++ ){
    source[i] = 0xdeadbeef;
    dest[i] = 0;
  }

  /* perform a barrier */
  xbrtime_barrier_all();

  if( xbrtime_mype() == 0 ){
    /* perform an operation */
    xbrtime_long_put_nbi(dest, source, TEST_SIZE, 1);
  }

  xbrtime_barrier_all();

  // Validate the results
  if( xbrtime_mype() == 1 ){
    for( int i=0; i<TEST_SIZE; i++ ){
      if( dest[i] != 0xdeadbeef ){
        printf("Error detected in put_long_test: dest[%d]=%x\n", i, dest[i]);
      }
    }
  }
  xbrtime_free( dest );
  xbrtime_close();
  free( source );
  
  return 0;
}

/* EOF */
