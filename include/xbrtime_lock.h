/*
 * _XBRTIME_LOCK_H_
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

#ifndef _XBRTIME_LOCK_H_
#define _XBRTIME_LOCK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

enum {
  XBGAS_LOCK_NULL_PE = -1,
  XBGAS_LOCK_WAITING,
  XBGAS_LOCK_PROCEEDING
};

typedef struct mcs_node{
  int next;     // i.e. tail in the lock owner
  int waiting;
} mcs_node_t;

void xbrtime_init_lock(long *lock);
void xbrtime_set_lock(long *lock);
void xbrtime_clear_lock(long *lock);
int xbrtime_test_lock(long *lock);


#ifdef __cplusplus
}
#endif  /* extern "C" */

#endif /* _XBRTIME_LOCK_H_ */

/* EOF */
