/* _G_FLOAT_TEST_C_
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

int main( int argc, char **argv ){
  double *source;
  double dest = 0.01;

  xbrtime_init();
  int mype = xbrtime_mype();
  source = (double *)xbrtime_malloc( sizeof(double) );

  if (mype == 1)
    source[0] = 0.999;
  else
    source[0] = 0.0;

  xbrtime_barrier_all();

  if( mype == 0 )
    dest = xbrtime_double_g( source, 1 );

  xbrtime_barrier_all();

  if (mype == 0) 
    printf("Dest: %.3f\n", dest);

  xbrtime_free( source );
  xbrtime_close();

  return 0;
}

/* EOF */
