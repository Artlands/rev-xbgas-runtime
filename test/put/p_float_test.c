/* _P_INT_TEST_C_
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

#include "xbrtime.h"

// TODO: the floating-point value is not being transferred correctly
int main( int argc, char **argv ){
  float source = -11.22;
  float *dest;

  xbrtime_init();
  int mype = xbrtime_mype();
  
  dest = (float *)xbrtime_malloc( sizeof(float) );
  dest[0] = (float)(mype + 5.55);

  if( mype == 0 )
    xbrtime_float_p( dest, source, 1 );

  xbrtime_barrier_all();

  // if (mype == 1) 
  //   printf("Dest[0]: %.2f\n", dest[0]);
  printf("PE %d: Dest[0]: %.2f\n", mype, dest[0]);

  xbrtime_free( dest );
  xbrtime_close();

  return 0;
}

/* EOF */
