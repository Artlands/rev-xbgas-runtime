/* _INIT_TEST_4_C_
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

// #include <stdio.h>
#include "xbrtime.h"

int main( int argc, char **argv ){
  int rtn = 0;

  printf( "Initializing xBGAS Runtime\n" );
  rtn = xbrtime_init();
  printf( "xBGAS is Initialized; Closing xBGAS\n" );

  printf( "I AM PE=%d of %d TOTAL PEs\n",
          xbrtime_mype(),
          xbrtime_num_pes() );


  xbrtime_close();
  printf( "xBGAS is Closed\n" );

  return rtn;
}

/* EOF */
