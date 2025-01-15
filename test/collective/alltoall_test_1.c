/*
* _ALLTOALL_TEST_1_C_
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

int main()
{
  xbrtime_init();
  int mype = xbrtime_mype();
  int npes = xbrtime_num_pes();

  const int count = 2;
  int64_t *dest = (int64_t *)xbrtime_malloc(count * npes * sizeof(int64_t));
  int64_t *source = (int64_t *)xbrtime_malloc(count * npes * sizeof(int64_t));

  /* assign source values */
  for (int pe = 0; pe < npes; pe++) {
    for (int i = 0; i < count; i++) {
      source[((pe * count) + i)] = mype + i;
      dest[((pe * count) + i)] = 9999;
    }
  }

  if ( mype == 0 ) {
    printf("Before Alltoall\n");
    for (int i = 0; i < count * npes; i++) {
      printf("PE %d: source[%d] = %" PRId64 "\n", mype, i, source[i]);
    }
  }

  /* wait for all PEs to initialize source/dest */
  xbrtime_barrier_all();

  xbrtime_int64_alltoall(dest, source, count);

  /* verify results */
  for (int pe = 0; pe < npes; pe++) {
    for (int i = 0; i < count; i++) {
      int j = (pe * count) + i;
      if (dest[j] != pe + i) {
        printf("[%d] ERROR: dest[%d]=%" PRId64 ", should be %d\n", mype, j, dest[j],
        pe + i);
      }
    }
  }

  if ( mype == 0 ) {
    printf("After Alltoall\n");
    for (int i = 0; i < count * npes; i++) {
      printf("PE %d: dest[%d] = %" PRId64 "\n", mype, i, dest[i]);
    }
  }

  xbrtime_free(dest);
  xbrtime_free(source);
  xbrtime_close();

  return 0;
}