#include "xbrtime.h"
#include <stdio.h>

int main(void) {
  uint32_t *dest;
  int old = -1;
  xbrtime_init();
  int mype = xbrtime_mype();

  dest = (uint32_t *)xbrtime_malloc(1 * sizeof(uint32_t));
  dest[0] = 0b111000;
  
  if ( mype == 1 ) {
    old = xbrtime_uint32_atomic_fetch_xor(&dest[0], 0b111000, 0);
  }
  xbrtime_barrier();
  printf("%d: dst = %" PRIu32 ", old = %d", mype, dest[0], old);

  xbrtime_free(dest);
  xbrtime_close();
  return 0;
}