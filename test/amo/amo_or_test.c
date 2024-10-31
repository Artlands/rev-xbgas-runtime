#include "xbrtime.h"
#include <stdio.h>

int main(void) {
  uint32_t *dest;
  xbrtime_init();
  int mype = xbrtime_mype();

  dest = (uint32_t *)xbrtime_malloc(1 * sizeof(uint32_t));
  dest[0] = 0b111000;
  
  if ( mype == 1 ) {
    xbrtime_uint32_atomic_or(&dest[0], 0b000111, 0);
  }
  xbrtime_barrier();
  printf("%d: dst = %" PRIu32 "", mype, dest[0]);

  xbrtime_free(dest);
  xbrtime_close();
  return 0;
}