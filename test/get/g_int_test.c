/* _G_INT_TEST_C_
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
  int *source;
  int dest;

  xbrtime_init();
  int mype = xbrtime_mype();
  source = (int *)xbrtime_malloc( sizeof(int) );

  if (mype == 1)
    source[0] = -999;
  else
    source[0] = 0;

  xbrtime_barrier();

  if( mype == 0 )
    dest = xbrtime_int_g( source, 1 );

  xbrtime_barrier();

  if (mype == 0) 
    printf("Dest: %d", dest);

  xbrtime_free( source );
  xbrtime_close();

  return 0;
}

/* EOF */
