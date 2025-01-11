/* _AMO_FETCH_INC_TEST_C_
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

int main(void) {
  int *dest;
  int old = -1;
  xbrtime_init();
  int mype = xbrtime_mype();

  dest = (int *)xbrtime_malloc(1 * sizeof(int));
  dest[0] = 22;
  
  if ( mype == 0 ) {
    old = xbrtime_int_atomic_fetch_inc(&dest[0], 1);
  }
  xbrtime_barrier_all();
  printf("PE %d: old = %d, dst = %d\n", mype, old, dest[0]);

  xbrtime_free(dest);
  xbrtime_close();
  return 0;
}

/* EOF */