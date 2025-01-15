/* _P_INT_TEST_C_
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

int main( int argc, char **argv ){
  int source = -11;
  int *dest;

  xbrtime_init();
  int mype = xbrtime_mype();
  
  dest = (int *)xbrtime_malloc( sizeof(int) );
  dest[0] = 999;

  if( mype == 0 )
    xbrtime_int_p( dest, source, 1 );

  xbrtime_barrier_all();

  if (mype == 1) 
    printf("Dest[0]: %d\n", dest[0]);

  xbrtime_free( dest );
  xbrtime_close();

  return 0;
}

/* EOF */
