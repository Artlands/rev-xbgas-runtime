/* _LOCK_TEST_2_C_
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
  int mype = xbrtime_mype();

  long *lock = (long *)xbrtime_malloc(1 * sizeof(long));
  lock[0] = 0;
  int *count = (int *)xbrtime_malloc(1 * sizeof(int));
  count[0] = 0;

  xbrtime_barrier_all();
  
  xbrtime_init_lock(lock);

  int test = xbrtime_test_lock(lock);

  if ( test == 1 ) {
    printf("PE %d: Lock is busy. Do nothing.\n", mype);
  } else {
    printf("PE %d: Lock is free. Get the lock.\n", mype);
    int val = xbrtime_int_g(count, 0); /* get count value on PE 0 */
    val++; /* incrementing and updating count on PE 0 */
    xbrtime_int_p(count, val, 0);
    printf("PE %d: Free the lock.\n", mype);
    xbrtime_clear_lock(lock); /* ensures count update completes before clearing the lock */
  }
  
  xbrtime_barrier_all();

  if (mype == 0)
    printf("Result: PE %d: count is %d\n", mype, count[0]);

  xbrtime_free(lock);
  xbrtime_free(count);
  xbrtime_close();
  return 0;
}

/* EOF */