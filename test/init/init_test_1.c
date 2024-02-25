/* _INIT_TEST_1_C_
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
  int rtn = 0;

  printf( "Initializing xBGAS Runtime\n");
  rtn = xbrtime_init();

  int pe = xbrtime_mype();
  printf( "PE %d: xBGAS is Initialized\n", pe );  
  return rtn;
}

/* EOF */
