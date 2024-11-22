/* _P_LONG_TEST_C_
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
#include "xbrtime.h"

int main( int argc, char **argv ){
  long source = 0xdeadbeef;
  long *dest;

  xbrtime_init();
  int mype = xbrtime_mype();
  
  dest = (long *)xbrtime_malloc( sizeof(long) );
  dest[0] = 0x0;

  if( mype == 0 )
    xbrtime_long_p( dest, source, 1 );

  xbrtime_barrier_all();

  if (mype == 1) 
    printf("Dest[0]: 0x%x", dest[0]);

  xbrtime_free( dest );
  xbrtime_close();

  return 0;
}

/* EOF */
