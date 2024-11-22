/* _G_LONG_TEST_C_
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
  long *source;
  long dest;

  xbrtime_init();
  int mype = xbrtime_mype();
  source = (long *)xbrtime_malloc( sizeof(long) );

  if (mype == 1)
    source[0] = 0xdeadbeef;
  else
    source[0] = 0x0;

  xbrtime_barrier_all();

  if( mype == 0 )
    dest = xbrtime_long_g( source, 1 );

  xbrtime_barrier_all();

  if (mype == 0) 
    printf("Dest: 0x%x", dest);

  xbrtime_free( source );
  xbrtime_close();

  return 0;
}

/* EOF */
