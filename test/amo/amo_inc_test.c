#include "xbrtime.h"
#include <stdio.h>

int main(void) {
  int *dest;
  xbrtime_init();
  int mype = xbrtime_mype();

  dest = (int *)xbrtime_malloc(1 * sizeof(int));
  dest[0] = 74;
  
  if ( mype == 0 ) {
    xbrtime_int_atomic_inc(&dest[0], 1);
  }
  xbrtime_barrier();
  printf("%d: dst = %d", mype, dest[0]);

  xbrtime_free(dest);
  xbrtime_close();
  return 0;
}