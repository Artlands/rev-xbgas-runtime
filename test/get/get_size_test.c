/* _GET_LONG_TEST_C_
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

#define TEST_SIZE 32

int main( int argc, char **argv ){
  int mype, npes;
  void *dest = malloc( TEST_SIZE );

  xbrtime_init();
  mype = xbrtime_mype();

  // Symmetric memory allocation
  void *source = (void *)(xbrtime_malloc( TEST_SIZE ));

  // Initialize the source and dest array
  memset(dest, 0, TEST_SIZE);
  memset(source, mype, TEST_SIZE);

  /* perform a barrier */
  xbrtime_barrier_all();

  if( xbrtime_mype() == 0 ){
    /* perform an operation */
    xbrtime_get16(dest, source, 2, 1);
  }

  xbrtime_barrier_all();

  if( xbrtime_mype() == 0 ){
    uint8_t *tmp = (uint8_t *)dest;
    for( int i=0; i<TEST_SIZE; i++ ){
      if( *tmp != 1 ){
        printf("Error detected in dest array at index %d; expected %d, but received %d\n", i, 1, *tmp);
      }
      *tmp++;
    }
  }

  xbrtime_free( source );
  xbrtime_close();
  free( dest );
  
  return 0;
}

/* EOF */
