/* _IPUT_LONG_TEST_C_
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

int main( int argc, char **argv ){
  int mype, npes;
  long source[10] = { 0xAAAAAAAA, 0xBBBBBBBB, 0xCCCCCCCC, 0xDDDDDDDD, 0xEEEEEEEE, 0xFFFFFFFF, 0x11111111, 0x22222222, 0x33333333, 0x44444444 };

  xbrtime_init();
  mype = xbrtime_mype();

  // Symmetric memory allocation
  long *dest = (long *)(xbrtime_malloc( sizeof(long) * 10 ));

  for (int i = 0; i < 10; i++) {
    dest[i] = 0x00;
  }

  xbrtime_barrier_all(); 

  if( xbrtime_mype() == 0 ){
    /* perform an operation */
    xbrtime_long_iput(dest, source, 1, 2, 5, 1);
  }

  xbrtime_barrier_all();

  if (mype == 1) {
    for (int i = 0; i < 10; i++) {
      printf("dest[%d] = 0x%x", i, dest[i]);
    }
  }
  xbrtime_free( dest );
  xbrtime_close();

  return 0;
}

/* EOF */
