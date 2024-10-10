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
#include "dataset1.h"

#define ITERS 500
#define STRIDE 1

int main()
{
  uint64_t *array;
  int *target;

  if( ELEMS < ITERS ) {
    printf( "Number of elements is too small for iteration count; increase the number of elements or reduce the iteratoin count." );
    return 1;
  }

  // test to see whether we'll stride out of bounds
  uint64_t end = (ITERS * STRIDE) - STRIDE;
  if ( end > ELEMS ){
    printf( "Stride will cause out of bounds access; reduce the stride or increase the number of elements" );
    return 1;
  }

  /* Initialize the runtime */ 
  xbrtime_init();

  if ( xbrtime_mype() == 0 ){
    printf( "XBGAS Atomic Compare and Swap Test 1; PEs = %d", xbrtime_num_pes() );
  }

  xbrtime_barrier();

  // array resides in symmetric heap space
  array = (uint64_t *)xbrtime_malloc( ELEMS * sizeof(uint64_t) );

  if ( array == NULL ){
    printf( "Array could not be allocated" );
    xbrtime_close();
    return 1;
  }

  // target resides in local PE memory
  target = (int *)(malloc( sizeof( int ) * ITERS ));

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
    for( unsigned i=0; i< ITERS; i++ ){
      target[i] = 0;
    }
  } else {
    for( unsigned i=0; i< ITERS; i++ ){
      if( xbrtime_mype() == xbrtime_num_pes()-1 ){
        // last pe
        target[i] = 0;
      } else {
        target[i] = xbrtime_mype() + 1;
      }
    }
  }

  // Setup the array values
  for( unsigned i=0; i<ELEMS; i++ ){
    array[i] = 0x00;
  }

  if( xbrtime_mype() == 0 ){
    printf( "Done initializing XBGAS data members" );
  }

  xbrtime_barrier();

  struct __kernel_timespec s, e;
  int kams = 0;
  // Start the CAS test
  uint64_t start = 0;
  uint64_t idx = 0;

  rev_clock_gettime( 0, &s );
  for( unsigned i=0; i<ITERS; i++ ){
    start = (uint64_t) xbrtime_long_atomic_compare_swap((long *)(&array[idx]), (long)(0x00), (long)(input_data[i]), target[i]);
    idx += STRIDE;
  }
  rev_clock_gettime( 0, &e );

  xbrtime_barrier();

  kams = (int)((xbrtime_num_pes() * ITERS * 1.0e-3) / ((e.tv_nsec - s.tv_nsec) * 1.0e-9));

  if ( xbrtime_mype() == 0 ){
    printf( "XBGAS Atomic Compare and Swap Test 2-STRIDE%d: Complete ", STRIDE );
    printf( " Total iterations: %d ", ITERS * xbrtime_num_pes() );
    printf( " Time: %d ns ", (e.tv_nsec - s.tv_nsec));
    printf( " KAMS: %d Kilo AMOs/second", kams );
  }

  // Print out the first 5 elements
  if ( xbrtime_mype() == 0 ){
    printf( "First 5 elements: " );
    for( unsigned i=0; i<5; i++ ){
      printf( "array[%d] = 0x%lx ", i, array[i] );
    }
  }

  xbrtime_close();

}

/* EOF */
