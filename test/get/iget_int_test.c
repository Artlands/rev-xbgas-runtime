/* _IGET_INT_TEST_C_
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
  int mype, npes;
  int dest[10] = {99, 99, 99, 99, 99, 99, 99, 99, 99, 99};

  xbrtime_init();
  mype = xbrtime_mype();

  // Symmetric memory allocation
  int *source = (int *)(xbrtime_malloc( sizeof(int) * 10 ));

  for (int i = 0; i < 10; i++) {
    source[i] = i;
  }

  xbrtime_barrier_all(); 

  if( xbrtime_mype() == 0 ){
    /* perform an operation */
    xbrtime_int_iget(dest, source, 1, 2, 5, 1);
  }

  xbrtime_barrier_all();

  if (mype == 0) {
    for (int i = 0; i < 10; i++) {
      printf("dest[%d] = %d\n", i, dest[i]);
    }
  }
  xbrtime_free( source );
  xbrtime_close();

  return 0;
}

/* EOF */
