/* _XFER_GET_TEST_1_C_
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

#ifndef ELEMS
#define ELEMS 1  // Default value if not defined
#endif

int main()
{
  uint64_t *array;
  uint64_t *dest;

  /* Initialize the runtime */ 
  xbrtime_init();

  if ( xbrtime_mype() == 0 ){
    printf( "XBGAS Bulk Get Test; PEs = %d", xbrtime_num_pes() );
  }

  xbrtime_barrier();

  // array resides in symmetric heap space
  array = (uint64_t *)xbrtime_malloc( ELEMS * sizeof(uint64_t) );

  if ( array == NULL ){
    printf( "Array could not be allocated" );
    xbrtime_close();
    return 1;
  }

  // dest resides in local PE memory
  dest = (uint64_t *)(malloc( ELEMS * sizeof(uint64_t) ));

  if ( dest == NULL ){
    printf( " dest could not be allocated" );
    xbrtime_free( array );
    xbrtime_close();
    return 1;
  }

  xbrtime_barrier();

  // Setup the array values
  for( unsigned i=0; i<ELEMS; i++ ){
    array[i] = (uint64_t)( xbrtime_mype() + i );
  }

  xbrtime_barrier();

  struct __kernel_timespec s, e;
  rev_clock_gettime( 0, &s );
  
  if ( xbrtime_mype() == 0 ){
    xbrtime_longlong_get_nb((long long *)(dest), (long long*)(array), ELEMS, 1, 1);
  }
  xbrtime_barrier();

  rev_clock_gettime( 0, &e );

  if ( xbrtime_mype() == 0 ){
    printf( " XBGAS Bulk Get Test (non-blocking): Complete " );
    printf( " Total elements: %d ", ELEMS );
    printf( " Time: %d ns ", (e.tv_nsec - s.tv_nsec));
  }

  // Find the smaller number between 5 and ELEMS
  int n = (5 < ELEMS) ? 5 : ELEMS;

  if ( xbrtime_mype() == 0 ) {
    // print first n elements
    for( unsigned i=0; i<n; i++ ){
      printf( "dest[%d] = %" PRIu64 " ", i, dest[i] );
    }
    if ( ELEMS > n) {
      // print last n elements
      for( unsigned i=ELEMS-n; i<ELEMS; i++ ){
        printf( "dest[%d] = %" PRIu64 " ", i, dest[i] );
      }
    }
  }

  xbrtime_close();
}

/* EOF */
