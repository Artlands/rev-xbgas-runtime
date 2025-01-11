/* _IPUT_CHAR_TEST_C_
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

int main( int argc, char **argv ){
  int mype, npes;
  char source[10] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };

  xbrtime_init();
  mype = xbrtime_mype();

  // Symmetric memory allocation
  char *dest = (char *)(xbrtime_malloc( sizeof(char) * 10 ));

  for (int i = 0; i < 10; i++) {
    dest[i] = '\0';
  }

  xbrtime_barrier_all(); 

  if( xbrtime_mype() == 0 ){
    /* perform an operation */
    xbrtime_char_iput(dest, source, 1, 2, 5, 1);
  }

  xbrtime_barrier_all();

  if (mype == 1) {
    for (int i = 0; i < 10; i++) {
      printf("dest[%d] = %c\n", i, dest[i]);
    }
  }
  xbrtime_free( dest );
  xbrtime_close();

  return 0;
}

/* EOF */
