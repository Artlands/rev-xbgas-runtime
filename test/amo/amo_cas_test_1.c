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
#include "rev-macros.h"

#define ELEMS 1204
#define STRIDE 8

int main()
{
  int *array;
  int *target;

  /* Initialize the runtime */
  xbrtime_init();

  if ( xbrtime_mype() == 0 ){
    printf( "XBGAS Atomic Compare and Swap Test 1; PEs = %d", xbrtime_num_pes() );
  }

  xbrtime_barrier();

  // array resides in symmetric heap space
  array = (int *)xbrtime_malloc( ELEMS * sizeof(int) );

  if ( array == NULL ){
    printf( "Array could not be allocated" );
    xbrtime_close();
    return 1;
  }

  // target resides in local PE memory
  target = (int *)(malloc( sizeof( int ) * xbrtime_num_pes()));

  if ( target == NULL ){
    printf( " Target could not be allocated" );
    xbrtime_free( array );
    xbrtime_close();
    return 1;
  }

  if ( xbrtime_mype() == 0 ) {
    printf( "Initializing xBGAS data members" );
  }

  xbrtime_barrier();

  // Init the target array
  if ( xbrtime_num_pes() == 1 ){
    for( unsigned i=0; i< xbrtime_num_pes(); i++ ){
      target[i] = 0;
    }
  } else {
    for( unsigned i=0; i< xbrtime_num_pes(); i++ ){
      if( xbrtime_mype() == xbrtime_num_pes()-1 ){
        // last pe
        target[i] = 0;
      } else {
        target[i] = xbrtime_mype() + 1;
      }
    }
  }

  // Setup the Idx and array values
  for( unsigned i=0; i<ELEMS; i++ ){
    array[i] = xbrtime_mype();
  }

  if( xbrtime_mype() == 0 ){
    printf( "Done initializing XBGAS data members" );
  }

  xbrtime_barrier();

  struct __kernel_timespec s, e;
  int kams = 0;
  // Start the CAS test
  int start = 0;

  rev_clock_gettime( 0, &s );
  for( unsigned i=0; i<ELEMS; i++ ){
    start = (int) xbrtime_int_atomic_compare_swap((int *)(&array[i]), (int)(target[i]), (int)(i), target[i]);
  }
  rev_clock_gettime( 0, &e );

  xbrtime_barrier();

  kams = (int)((xbrtime_num_pes() * ELEMS * 1.0e-3) / ((e.tv_nsec - s.tv_nsec) * 1.0e-9));

  if ( xbrtime_mype() == 0 ){
    printf( "XBGAS Atomic Compare and Swap Test 1-RAND: Complete " );
    printf( " Total iterations: %d ", ELEMS * xbrtime_num_pes() );
    printf( " Time: %d ns ", (e.tv_nsec - s.tv_nsec));
    printf( " KAMS: %d Kilo AMOs/second", kams );
  }

  if ( xbrtime_mype() == 0 ){
    printf( "First 5 elements: " );
    for( unsigned i=0; i<5; i++ ){
      printf( "array[%d] = 0x%d ", i, array[i] );
    }
  }

  xbrtime_close();

}

/* EOF */
