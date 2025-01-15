/* _AMO_CAS_TEST_C_
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
  int mype;
  int *race_winner;
  int oldval = 0;

  xbrtime_init();
  mype = xbrtime_mype();

  race_winner = (int *)xbrtime_malloc(1 * sizeof(int));
  race_winner[0] = -1;
  
  xbrtime_barrier_all();  

  // The following call ensures that the first PE to execute the conditional swap 
  // will successfully write its PE number to race_winner on PE 0.
  if (mype != 0)
    oldval = xbrtime_int_atomic_compare_swap(&race_winner[0], -1, mype, 0);

  xbrtime_barrier_all();
  if (oldval == -1)
    printf("PE %d was first\n", mype);

  printf("PE %d value = %d, race_winner = %d\n", mype, oldval, race_winner[0]);

  xbrtime_free(race_winner);
  xbrtime_close();
  return 0;
}

/* EOF */