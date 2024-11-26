/*
* _COLLECT_TEST_1_C_
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

  if ( npes != 2 ) {
    printf("This test requires 2 PEs");
    xbrtime_close();
    return 1;
  }

  int my_nelem = 2;
  int total_nelem = my_nelem * npes;

  int *source = (int *)xbrtime_malloc(npes * sizeof(int)); /* symmetric alloc */
  int *dest = (int *)xbrtime_malloc(total_nelem * sizeof(int));

  for (int i = 0; i < my_nelem; i++)
    source[i] = (mype * (mype + 1)) / 2 + i;
  for (int i = 0; i < total_nelem; i++)
    dest[i] = -9999;

  printf("PE %d: Source = %d %d", mype, source[0], source[1]);

  /* wait for all PEs to initialize source/dest */
  xbrtime_barrier_all();

  xbrtime_int_collect(dest, source, my_nelem);

  printf("PE %d: Dest = %d %d %d %d", mype, dest[0], dest[1], dest[2], dest[3]);
  
  xbrtime_free(dest);
  xbrtime_free(source);
  xbrtime_close();

  return 0;
}