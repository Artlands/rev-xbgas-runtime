/* _LOCK_TEST_3_C_
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
  int *count2 = (int *)xbrtime_malloc(1 * sizeof(int));
  count[0] = 0;
  count2[0] = 0;

  xbrtime_barrier_all();
  
  /* First lock */
  xbrtime_init_lock(lock);
  xbrtime_set_lock(lock);

  int val = xbrtime_int_g(count, 0); /* get count value on PE 0 */
  val++; /* incrementing and updating count on PE 0 */
  xbrtime_int_p(count, val, 0);

  xbrtime_clear_lock(lock); /* ensures count update completes before clearing the lock */

  xbrtime_barrier_all();

  if (mype == 0)
    printf("First Lock - Result: PE %d: count is %d\n", mype, count[0]);

  xbrtime_barrier_all();

  /* Second lock. Have to initialize the lock first*/
  xbrtime_init_lock(lock);
  xbrtime_set_lock(lock);

  val = xbrtime_int_g(count2, 0); /* get count value on PE 0 */
  val +=2; /* incrementing and updating count on PE 0 */
  xbrtime_int_p(count2, val, 0);

  xbrtime_clear_lock(lock); /* ensures count update completes before clearing the lock */

  xbrtime_barrier_all();

  if (mype == 0)
    printf("Second Lock - Result: PE %d: count is %d\n", mype, count2[0]);

  xbrtime_free(lock);
  xbrtime_free(count);
  xbrtime_free(count2);
  xbrtime_close();
  return 0;
}

/* EOF */