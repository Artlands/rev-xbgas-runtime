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


int main()
{
  int *array;
  int *idx;

  /* Initialize the runtime */ 
  xbrtime_init();

  if ( xbrtime_num_pes() > 2 ) {
    printf( "This test requires 2 PEs" );
    xbrtime_close();
    return 1;
  }

  if ( xbrtime_mype() == 0 ){
    printf( "XBGAS Atomic Compare and Swap Test 0; PEs = %d", xbrtime_num_pes() );
  } 

  xbrtime_barrier();

  // array resides in symmetric heap space
  array = (int *)xbrtime_malloc( sizeof(int) );

  if ( array == NULL ){
    printf( "Array could not be allocated" );
    xbrtime_close();
    return 1;
  }

  if ( xbrtime_mype() == 0 ) {
    printf( "Initializing xBGAS data members" );
  }

  xbrtime_barrier();

  array[0] = xbrtime_mype() + 1;

  printf( "PE %d; array[0] = %d ", xbrtime_mype(), array[0] );

  if( xbrtime_mype() == 0 ){
    printf( "Done initializing XBGAS data members" );
  }

  xbrtime_barrier();

  // Start the CAS test
  int start = 0;

  if ( xbrtime_mype() == 0 ) {
    // TRACE_ON
    start = (int) xbrtime_int_atomic_compare_swap((int *)(&array[0]), (int)(2), (int)(10), 1);
    // TRACE_OFF
  }
    
  xbrtime_barrier();

  printf( "CAS Test 0: PE %d; array[0] = %d, start = %d ", xbrtime_mype(), array[0], start);

  xbrtime_close();

  printf( "XBGAS Atomic Compare and Swap Test 0 complete" );
}

/* EOF */
