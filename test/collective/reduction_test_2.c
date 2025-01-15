/*
* _REDUCTION_TEST_1_C_
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
#include "reduction_input_2.h"


int main()
{
  xbrtime_init();
  int mype = xbrtime_mype();
  int npes = xbrtime_num_pes();

  if (npes != NPES) {
    printf("This test requires %d PEs\n", NPES);
    xbrtime_close();
    return 0;
  }

  int *values = xbrtime_malloc(NELEMS * sizeof(int));

  unsigned char *value_is_maximul = xbrtime_malloc(NELEMS * sizeof(unsigned char));
  unsigned char *value_is_maximal_all = xbrtime_malloc(NELEMS * npes * sizeof(unsigned char));

  int *maximal_values_count = xbrtime_malloc(sizeof(int));
  int *maximal_values_total = xbrtime_malloc(sizeof(int));

  for ( int i = 0; i < NELEMS; i++ ) {
    values[i] = input_data[mype][i];
    /* Track and count instances of maximal values (i.e., values equal to (npes-1)) */
    value_is_maximul[i] = (values[i] == (npes-1)) ? 1 : 0;
    maximal_values_count[0] += value_is_maximul[i];
  }

  /* Wait for all PEs to initialize reductions arrays */
  xbrtime_barrier_all();

  xbrtime_uchar_or_reduce(value_is_maximal_all, value_is_maximul, NELEMS);
  xbrtime_int_sum_reduce(maximal_values_total, maximal_values_count, 1);

  if (mype == 0) {
    printf("Found %d maximal random numbers across all PEs.\n", maximal_values_total[0]);
    printf("A maximal number occured (at least once) at the following indices:\n");
    for (int i = 0; i < NELEMS; i++) {
      if (value_is_maximal_all[i] == 1) {
        printf("%d ", i);
      }
    }
    printf("\n");
  }

  xbrtime_free(value_is_maximul);
  xbrtime_free(value_is_maximal_all);
  xbrtime_free(maximal_values_count);
  xbrtime_free(maximal_values_total);
  xbrtime_close();

  return 0;
}