/* _LOCK_TEST_C_
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

inline static int lock_owner( void *addr ) {
  const uint64_t ad = (uint64_t)addr;
  int num_pes = xbrtime_num_pes();
  int owner;
  owner = (ad >> 3) % num_pes;
  if ( owner == 0 ) {
    // Do not choose PE 0, as it is often used for work allocation
    owner = num_pes - 1;
  }
  return owner;
}

int main(void) {
  xbrtime_init();
  int mype = xbrtime_mype();

  long *lock = (long *)xbrtime_malloc(1 * sizeof(long));
  lock[0] = 0;
  int *count = (int *)xbrtime_malloc(1 * sizeof(int));
  count[0] = 0;

  xbrtime_barrier();
  
  xbrtime_init_lock(lock);

  xbrtime_set_lock(lock);

  int val = xbrtime_int_g(count, 0); /* get count value on PE 0 */
  val++; /* incrementing and updating count on PE 0 */
  xbrtime_int_p(count, val, 0);

  xbrtime_clear_lock(lock); /* ensures count update completes before clearing the lock */

  xbrtime_barrier();

  if (mype == 0)
    printf("Result: PE %d: count is %d", mype, count[0]);

  xbrtime_free(lock);
  xbrtime_free(count);
  xbrtime_close();
  return 0;
}

/* EOF */