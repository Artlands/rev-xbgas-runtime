#include "xbrtime.h"
#include <stdio.h>

int main(void) {
  int *dest;
  int old = -1;
  xbrtime_init();
  int mype = xbrtime_mype();

  dest = (int *)xbrtime_malloc(1 * sizeof(int));
  dest[0] = 22;
  
  if ( mype == 0 ) {
    old = xbrtime_int_atomic_fetch_inc(&dest[0], 1);
  }
  xbrtime_barrier();
  printf("%d: old = %d, dst = %d", mype, old, dest[0]);

  xbrtime_free(dest);
  xbrtime_close();
  return 0;
}