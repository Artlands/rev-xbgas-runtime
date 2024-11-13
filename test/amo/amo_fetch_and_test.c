/* _AMO_FETCH_AND_TEST_C_
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
  uint32_t *dest;
  int old = -1;
  xbrtime_init();
  int mype = xbrtime_mype();

  dest = (uint32_t *)xbrtime_malloc(1 * sizeof(uint32_t));
  dest[0] = 0b101010;
  
  if ( mype == 1 ) {
    old = xbrtime_uint32_atomic_fetch_and(&dest[0], 0b000111, 0);
  }
  xbrtime_barrier();
  printf("%d: dst = %" PRIu32 ", old = %d", mype, dest[0], old);

  xbrtime_free(dest);
  xbrtime_close();
  return 0;
}

/* EOF */