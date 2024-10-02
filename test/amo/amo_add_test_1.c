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
#include "idx1.h"

#define STRIDE 8

int main()
{
  uint64_t *array;
  uint64_t *idx;
  int *target;

  if( ELEMS < ITERS ) {
    printf( "Number of elements is too small for iteration count; increase the number of elements or reduce the iteratoin count." );
    return 1;
  }

  /* Initialize the runtime */ 
  xbrtime_init();

  if ( xbrtime_mype() == 0 ){
    printf( "XBGAS Atomic Add Test 1; PEs = %d", xbrtime_num_pes() );
  }

  xbrtime_barrier();

  // array resides in symmetric heap space
  array = (uint64_t *)xbrtime_malloc( ELEMS * sizeof(uint64_t) );

  if ( array == NULL ){
    printf( "Array could not be allocated" );
    xbrtime_close();
    return 1;
  }

  // idx resides in symmetric heap space
  idx = (uint64_t *)xbrtime_malloc( ITERS * sizeof(uint64_t) );

  if ( idx == NULL ){
    printf( " Idx could not be allocated" );
    xbrtime_free( array );
    xbrtime_close();
    return 1;
  }

  // target resides in local PE memory
  target = (int *)(malloc( sizeof( int ) * ITERS ));

  if ( target == NULL ){
    printf( " Target could not be allocated" );
    xbrtime_free( array );
    xbrtime_free( idx );
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
        target[i] = 1;
      } else {
        target[i] = xbrtime_mype() + 1;
      }
    }
  }

  // Setup the Idx and array values
  for( unsigned i=0; i<ITERS; i++ ){
    idx[i] = input_idx[i];
  }
  for( unsigned i=0; i<ELEMS; i++ ){
    array[i] = input_data[i];
  }

  if( xbrtime_mype() == 0 ){
    printf( "Done initializing XBGAS data members" );
  }

  xbrtime_barrier();

  struct __kernel_timespec s, e;
  int kams = 0;
  // Start the CAS test
  uint64_t start = 0;

  rev_clock_gettime( 0, &s );
  for( unsigned i=0; i<ITERS; i++ ){
    xbrtime_long_get((long *)(&start), (long *)(&idx[i]), 1, 1, target[i]);
    start = (uint64_t) xbrtime_long_atomic_add((long *)(&array[start]), (long)(0x01), target[i]);
  }
  rev_clock_gettime( 0, &e );

  kams = (int)((xbrtime_num_pes() * ITERS * 1.0e-3) / ((e.tv_nsec - s.tv_nsec) * 1.0e-9));

  if ( xbrtime_mype() == 0 ){
    printf( " XBGAS Atomic Add Test 1-RAND: Complete " );
    printf( " Total iterations: %d ", ITERS * xbrtime_num_pes() );
    printf( " Time: %d ns ", (e.tv_nsec - s.tv_nsec));
    printf( " KAMS: %d Kilo AMOs/second", kams );
  }

  xbrtime_close();

}

/* EOF */
