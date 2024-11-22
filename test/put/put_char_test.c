/* _PUT_CHAR_TEST_C_
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

#define TEST_SIZE 1024

int main( int argc, char **argv ){
  int mype, npes;
  char *source = malloc( sizeof(char) * TEST_SIZE );

  xbrtime_init();
  mype = xbrtime_mype();

  // Symmetric memory allocation
  char *dest = (char *)(xbrtime_malloc( sizeof(char) * TEST_SIZE ));

  // Initialize the source and dest array
  for( int i=0; i<TEST_SIZE; i++ ){
    source[i] = 'A';
    dest[i] = 'B';
  }

  /* perform a barrier */
  xbrtime_barrier_all();

  if( xbrtime_mype() == 0 ){
    /* perform an operation */
    xbrtime_char_put(dest, source, TEST_SIZE, 1);
  }

  xbrtime_barrier_all();

  // Validate the results
  if( xbrtime_mype() == 1 ){
    for( int i=0; i<TEST_SIZE; i++ ){
      if( dest[i] != 'A' ){
        printf("Error detected in dest array at index %d; expected %c, but received %c", i, 'A', dest[i]);
      }
    }
  }
  xbrtime_free( dest );
  xbrtime_close();
  free( source );
  
  return 0;
}

/* EOF */
