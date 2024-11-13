/* _P_CHAR_TEST_C_
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

#include <stdio.h>
#include "xbrtime.h"

int main( int argc, char **argv ){
  char source = 'A';
  char *dest;

  xbrtime_init();
  int mype = xbrtime_mype();
  
  dest = (char *)xbrtime_malloc( sizeof(char) );
  dest[0] = '\0';

  if( mype == 0 )
    xbrtime_char_p( dest, source, 1 );

  xbrtime_barrier();

  if (mype == 1) 
    printf("Dest[0]: %c", dest[0]);

  xbrtime_free( dest );
  xbrtime_close();

  return 0;
}

/* EOF */
