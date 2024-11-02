/* _IGET_LONG_TEST_C_
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

#include <stdio.h>
#include <inttypes.h>
#include "xbrtime.h"

int main( int argc, char **argv ){
  int mype, npes;
  long dest[10] = {0x00};

  xbrtime_init();
  mype = xbrtime_mype();

  // Symmetric memory allocation
  long *source = (long *)(xbrtime_malloc( sizeof(long) * 10 ));

  for (int i = 0; i < 10; i++) {
    source[i] = 0xdeafbeef + i;
  }

  if( xbrtime_mype() == 0 ){
    /* perform an operation */
    xbrtime_long_iget(dest, source, 1, 2, 5, 1);
  }

  xbrtime_barrier();

  if (mype == 0) {
    for (int i = 0; i < 10; i++) {
      printf("dest[%d] = 0x%x", i, dest[i]);
    }
  }
  xbrtime_free( source );
  xbrtime_close();

  return 0;
}

/* EOF */
