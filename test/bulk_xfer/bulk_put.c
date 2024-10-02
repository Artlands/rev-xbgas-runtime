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
    printf( "XBGAS Bulk Put Test; PEs = %d", xbrtime_num_pes() );
  }

  xbrtime_barrier();

  // dest resides in symmetric heap space
  dest = (uint64_t *)xbrtime_malloc( ELEMS * sizeof(uint64_t) );

  if ( dest == NULL ){
    printf( "Array could not be allocated" );
    xbrtime_close();
    return 1;
  }

  // dest resides in local PE memory
  array = (uint64_t *)(malloc( ELEMS * sizeof(uint64_t) ));

  if ( array == NULL ){
    printf( " dest could not be allocated" );
    xbrtime_free( dest );
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

  if ( xbrtime_mype() == 0 ){
    rev_clock_gettime( 0, &s );

    xbrtime_longlong_put((long long *)(dest), (long long*)(array), ELEMS, 1, 1);

    rev_clock_gettime( 0, &e );
    printf( " XBGAS Bulk Put Test: Complete " );
    printf( " Total elements: %d ", ELEMS );
    printf( " Time: %d ns ", (e.tv_nsec - s.tv_nsec));
  }

  xbrtime_close();
}

/* EOF */
