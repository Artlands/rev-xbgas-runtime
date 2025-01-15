/* _BARRIER_TEST_1_C_
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

int main(void) {
  xbrtime_init();

  int npes = xbrtime_num_pes();
  if (npes < 2) {
    printf("This test requires at least 2 PEs\n");
    xbrtime_close();
    return 0;
  }

  printf("PE %d : first barrier!\n", xbrtime_mype());
  xbrtime_barrier_all();
  
  printf("PE %d : second barrier!\n", xbrtime_mype());
  xbrtime_barrier_all(); 

  xbrtime_close();
  return 0;
}

/* EOF */