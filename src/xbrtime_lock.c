/*
 * _XBRTIME_ALLOC_C_
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

// #define _LOCK_DEBUG_

/* Use basic MCS distributed lock algorithm for lock */

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

void xbrtime_init_lock(long *lock){
  mcs_node_t *mcs_node = (mcs_node_t *)lock;
  mcs_node->next = XBGAS_LOCK_NULL_PE;
  mcs_node->waiting = XBGAS_LOCK_WAITING;

#ifdef _LOCK_DEBUG_
  int mype = xbrtime_mype();
  printf("XBRTIME_DEBUG : PE %d: Initialize lock at %p\n", mype, lock);
#endif

}

void xbrtime_set_lock(long *lock){
  int mype = xbrtime_mype();
  mcs_node_t *mcs_node = (mcs_node_t *)lock;
  // Get the previous PE from the next/tail of the lock owner, and set the next/tail to myself
#ifdef _LOCK_DEBUG_
  printf("XBRTIME_DEBUG : PE %d: Atomic swap %p on %d with %d\n", mype, &mcs_node->next, lock_owner(lock), mype);
#endif

  int prev = xbrtime_int_atomic_swap(&mcs_node->next, mype, lock_owner(lock));

#ifdef _LOCK_DEBUG_
  printf("XBRTIME_DEBUG : PE %d: Previous PE %d\n", mype, prev);
#endif

  if ( prev != XBGAS_LOCK_NULL_PE ) {
    // Add myself to the end of the queue
    xbrtime_int_atomic_set(&mcs_node->next, mype, prev);

#ifdef _LOCK_DEBUG_
    printf("XBRTIME_DEBUG : PE %d: Atomic set %p on %d with %d\n", mype, &mcs_node->next, prev, mype);
#endif

    // Spin until the lock is released
    while(mcs_node->waiting == XBGAS_LOCK_WAITING) {
      asm volatile("nop");
    };
  }
}

void xbrtime_clear_lock(long *lock){
  int mype = xbrtime_mype();
  mcs_node_t *mcs_node = (mcs_node_t *)lock;

#ifdef _LOCK_DEBUG_
    printf("XBRTIME_DEBUG : PE %d: mcs_node->next = %d\n", mype, mcs_node->next);
#endif

  if ( mcs_node->next == XBGAS_LOCK_NULL_PE ) {
    return;
  }

#ifdef _LOCK_DEBUG_
  printf("XBRTIME_DEBUG : PE %d: Release the next PE %d, set waiting to %d\n", mype, mcs_node->next, XBGAS_LOCK_PROCEEDING);
#endif

  // Release the next PE
  xbrtime_int_atomic_set(&mcs_node->waiting, XBGAS_LOCK_PROCEEDING, mcs_node->next);
}

int xbrtime_test_lock(long *lock){
  int mype = xbrtime_mype();
  mcs_node_t *mcs_node = (mcs_node_t *)lock;
  // Get the previous PE from the next/tail of the lock owner
#ifdef _LOCK_DEBUG_
  printf("XBRTIME_DEBUG : PE %d: Atomic swap %p on %d with %d\n", mype, &mcs_node->next, lock_owner(lock), mype);
#endif

  int prev = xbrtime_int_atomic_fetch(&mcs_node->next, lock_owner(lock));

#ifdef _LOCK_DEBUG_
  printf("XBRTIME_DEBUG : PE %d: Previous PE %d\n", mype, prev);
#endif

  if ( prev != XBGAS_LOCK_NULL_PE ) {
    return 1;
  } else {
    xbrtime_int_atomic_set(&mcs_node->next, mype, lock_owner(lock));
    return 0;
  }
}