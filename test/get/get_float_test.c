/* _GET_INT_TEST_C_
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

#define TEST_SIZE 4

int main( int argc, char **argv ){
  int mype, npes;
  float *dest = malloc( sizeof(float) * TEST_SIZE );

  xbrtime_init();
  mype = xbrtime_mype();

  // Symmetric memory allocation
  float *source = (float *)(xbrtime_malloc( sizeof(float) * TEST_SIZE ));

  // Initialize the source and dest array
  for( int i=0; i<TEST_SIZE; i++ ){
    source[i] = (float) (i + 0.55 + mype);
    dest[i] = 0.0;
  }

  /* perform a barrier */
  xbrtime_barrier_all();

  if( xbrtime_mype() == 0 ){
    /* perform an operation */
    xbrtime_float_get(dest, source, TEST_SIZE, 1);
  }

  xbrtime_barrier_all();

  // Validate the results
  if( xbrtime_mype() == 0 ){
    for( int i=0; i<TEST_SIZE; i++ ){
      // if( dest[i] != i ){
      //   printf( "Error detected in get_int_test: dest[%d] = %d", i, dest[i] );
      // }
      printf( "Dest[%d]: %.3f\n", i, dest[i] );
    }
  }
  xbrtime_free( source );
  xbrtime_close();
  free( dest );
  
  return 0;
}

/* EOF */
