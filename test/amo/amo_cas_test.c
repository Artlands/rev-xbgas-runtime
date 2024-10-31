#include "xbrtime.h"
#include <stdio.h>

// The following call ensures that the first PE to execute the conditional swap will successfully
// write its PE number to race_winner on PE 0.
// Fix me: segmentation fault when pe > 3 with MemH as the memory backend
int main(void) {
  int mype;
  int *race_winner;
  int oldval = 0;

  xbrtime_init();
  mype = xbrtime_mype();

  race_winner = (int *)xbrtime_malloc(1 * sizeof(int));
  race_winner[0] = -1;
  
  xbrtime_barrier();

  if (mype != 0)
    oldval = xbrtime_int_atomic_compare_swap(&race_winner[0], -1, mype, 0);

  xbrtime_barrier();
  if (oldval == -1)
    printf("PE %d was first", mype);

  printf("PE %d value = %d, race_winner = %d", mype, oldval, race_winner[0]);

  xbrtime_free(race_winner);
  xbrtime_close();
  return 0;
}