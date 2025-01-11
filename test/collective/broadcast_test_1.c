/*
* _BROADCAST_TEST_1_C_
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

int main()
{
  xbrtime_init();
  int mype = xbrtime_mype();
  int npes = xbrtime_num_pes();

  long *source = (long *)xbrtime_malloc(4 * sizeof(long));
  long *dest = (long *)xbrtime_malloc(4 * sizeof(long));

  if ( mype == 0 ) {
    for(int i = 0; i < 4; i++) {
      source[i] = i;
    }
  }

  /* wait for all PEs to initialize source/dest */
  xbrtime_barrier_all();

  xbrtime_long_broadcast(dest, source, 4, 0);

  printf("PE %d: %ld %ld %ld %ld\n", mype, dest[0], dest[1], dest[2], dest[3]);

  xbrtime_free(dest);
  xbrtime_free(source);
  xbrtime_close();

  return 0;
}