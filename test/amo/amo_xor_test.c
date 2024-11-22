/* _AMO_XOR_TEST_C_
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
  xbrtime_init();
  int mype = xbrtime_mype();

  dest = (uint32_t *)xbrtime_malloc(1 * sizeof(uint32_t));
  dest[0] = 0b111000;
  
  if ( mype == 1 ) {
    xbrtime_uint32_atomic_xor(&dest[0], 0b000111, 0);
  }
  xbrtime_barrier_all();
  printf("%d: dst = %" PRIu32 "", mype, dest[0]);

  xbrtime_free(dest);
  xbrtime_close();
  return 0;
}

/* EOF */