/*
* _ALLTOALLS_TEST_1_C_
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

  const int count = 1;
  const ptrdiff_t dst = 2;
  const ptrdiff_t sst = 3;
  int64_t *dest = (int64_t *)xbrtime_malloc(count * dst * npes * sizeof(int64_t));
  int64_t *source = (int64_t *)xbrtime_malloc(count * sst * npes * sizeof(int64_t));

  /* assign source values */
  for (int pe = 0; pe < npes; pe++) {
    for (int i = 0; i < count; i++) {
      source[sst * ((pe * count) + i)] = mype + i;
      dest[dst * ((pe * count) + i)] = 9999;
    }
  }

  if ( mype == 1 ) {
    printf("Before Alltoalls");
    for (int i = 0; i < count * sst * npes; i++) {
      printf("source[%d] = %" PRId64 "", i, source[i]);
    }
  }

  /* wait for all PEs to initialize source/dest */
  xbrtime_barrier_all();

  xbrtime_int64_alltoalls(dest, source, dst, sst, count);

  /* verify results */
  for (int pe = 0; pe < npes; pe++) {
    for (int i = 0; i < count; i++) {
      int j = dst * ((pe * count) + i);
      if (dest[j] != pe + i) {
        printf("[%d] ERROR: dest[%d]=%" PRId64 ", should be %d", mype, j, dest[j], pe + i);
      }
    }
  }

  if ( mype == 1 ) {
    printf("After Alltoalls");
    for (int i = 0; i < count * dst * npes; i++) {
      printf("dest[%d] = %" PRId64 "", i, dest[i]);
    }
  }

  xbrtime_free(dest);
  xbrtime_free(source);
  xbrtime_close();

  return 0;
}