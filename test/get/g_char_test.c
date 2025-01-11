/* _G_CHAR_TEST_C_
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
  char *source;
  char dest;

  xbrtime_init();
  int mype = xbrtime_mype();
  source = (char *)xbrtime_malloc( sizeof(char) );

  if (mype == 1)
    source[0] = 'B';
  else
    source[0] = '\0';

  xbrtime_barrier_all();

  if( mype == 0 )
    dest = xbrtime_char_g( source, 1 );

  xbrtime_barrier_all();

  if (mype == 0) 
    printf("Dest: %c\n", dest);

  xbrtime_free( source );
  xbrtime_close();

  return 0;
}

/* EOF */
