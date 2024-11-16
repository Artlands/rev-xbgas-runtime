/* _PUT_INT_TEST_C_
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

// Todo: Debug failed if TEST_SIZE * sizeof(long) > 4096. 
// The program will stall on the last xbrtime_barrier()

#define TEST_SIZE 1000

int main( int argc, char **argv ){
  int mype, npes;
  int *source = malloc( sizeof(int) * TEST_SIZE );

  xbrtime_init();
  mype = xbrtime_mype();

  // Symmetric memory allocation
  int *dest = (int *)(xbrtime_malloc( sizeof(int) * TEST_SIZE ));

  // Initialize the source and dest array
  for( int i=0; i<TEST_SIZE; i++ ){
    source[i] = mype;
    dest[i] = 99;
  }

  /* perform a barrier */
  xbrtime_barrier();

  if( xbrtime_mype() == 0 ){
    /* perform an operation */
    xbrtime_int_put(dest, source, TEST_SIZE, 1);
  }

  xbrtime_barrier();

  // Validate the results
  if( xbrtime_mype() == 1 ){
    for( int i=0; i<TEST_SIZE; i++ ){
      if( dest[i] != 0 ){
        printf( "Error detected in dest[%d] = %d", i, dest[i] );
      }
    }
  }
  xbrtime_free( dest );
  xbrtime_close();
  free( source );
  
  return 0;
}

/* EOF */
