/* _AMO_SWAP_TEST_C_
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
#include <stdio.h>


int main(void) {
  int *dest;

  xbrtime_init();
  int mype = xbrtime_mype();
  int npes = xbrtime_num_pes();

  dest = (int *)xbrtime_malloc(1 * sizeof(int));
  dest[0] = mype;
  
  xbrtime_barrier();
  int new_val = mype;
  if ( mype & 1 ) {
    int swapped_val = xbrtime_int_atomic_swap(&dest[0], new_val, (mype + 1) % npes);
    printf("%d: dest = %ld, swapped = %ld", mype, dest[0], swapped_val);
  }

  xbrtime_free(dest);
  xbrtime_close();
  return 0;
}

/* EOF */