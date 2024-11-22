/* _IPUT_INT_TEST_C_
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
  int source[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  xbrtime_init();
  mype = xbrtime_mype();

  // Symmetric memory allocation
  int *dest = (int *)(xbrtime_malloc( sizeof(int) * 10 ));

  for (int i = 0; i < 10; i++) {
    dest[i] = 99;
  }

  xbrtime_barrier_all(); 

  if( xbrtime_mype() == 0 ){
    /* perform an operation */
    xbrtime_int_iput(dest, source, 1, 2, 5, 1);
  }

  xbrtime_barrier_all();

  if (mype == 1) {
    for (int i = 0; i < 10; i++) {
      printf("dest[%d] = %d", i, dest[i]);
    }
  }
  xbrtime_free( dest );
  xbrtime_close();

  return 0;
}

/* EOF */
