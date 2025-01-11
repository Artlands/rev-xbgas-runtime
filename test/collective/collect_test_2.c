/*
* _COLLECT_TEST_2_C_
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

  int my_nelem = 4;
  int total_nelem = my_nelem * npes;

  int *source = (int *)xbrtime_malloc(npes * sizeof(int)); /* symmetric alloc */
  int *dest = (int *)xbrtime_malloc(total_nelem * sizeof(int));
  long *lock = (long *)xbrtime_malloc(sizeof(long));
  xbrtime_init_lock(lock);

  for (int i = 0; i < my_nelem; i++)
    source[i] = (mype * (mype + 1)) / 2 + i;
  for (int i = 0; i < total_nelem; i++)
    dest[i] = -9999;

  /* wait for all PEs to initialize source/dest */
  xbrtime_barrier_all();

  xbrtime_int_collect(dest, source, my_nelem);

  xbrtime_set_lock(lock);

  printf("PE %d: Dest:\n", mype);
  for (int i = 0; i < total_nelem; i++)
    printf("dest[%d] = %d\n", i, dest[i]);

  xbrtime_clear_lock(lock);
  
  xbrtime_free(dest);
  xbrtime_free(source);
  xbrtime_free(lock);
  xbrtime_close();

  return 0;
}