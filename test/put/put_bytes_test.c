/* _PUT_CHAR_TEST_C_
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

#define TEST_SIZE 16

int main( int argc, char **argv ){
  int mype, npes;
  void *source = malloc( TEST_SIZE );

  xbrtime_init();
  mype = xbrtime_mype();

  // Symmetric memory allocation
  void *dest = xbrtime_malloc( TEST_SIZE );

  // Initialize the source and dest array
  memset(dest, 0, TEST_SIZE);
  memset(source, mype, TEST_SIZE);

  /* perform a barrier */
  xbrtime_barrier_all();

  if( xbrtime_mype() == 1 ){
    /* perform an operation */
    xbrtime_putmem(dest, source, TEST_SIZE, 0);
  }

  xbrtime_barrier_all();

  // Validate the results
  if( xbrtime_mype() == 0 ){
    uint8_t *tmp = (uint8_t *)dest;
    for( int i=0; i<TEST_SIZE; i++ ){
      if( *tmp != 1 ){
        printf("Error detected in dest array at index %d; expected %d, but received %d\n", i, 1, *tmp);
      }
      *tmp++;
    }
  }

  xbrtime_free( dest );
  xbrtime_close();
  free( source );
  
  return 0;
}

/* EOF */
