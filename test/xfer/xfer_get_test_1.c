/* _XFER_GET_TEST_1_C_
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
#include <inttypes.h>
#include "xbrtime.h"

#define _XBGAS_ALLOC_SIZE_ 8

int main()
{
  int rtn       = 0;
  uint64_t *ptr = NULL;
  size_t sz     = _XBGAS_ALLOC_SIZE_;

  /* Initialize the runtime */ 
  rtn = xbrtime_init();

  /* Allocate a symmetric memory region */
  ptr = (uint64_t *)(xbrtime_malloc( sz ));

  /* Initialize the symmetric memory region */
  ptr[0] = (uint64_t)(xbrtime_mype());

  /* perform a barrier */
  xbrtime_barrier();

  if( xbrtime_mype() == 0 ){
    /* perform an operation */
    xbrtime_ulonglong_get((unsigned long long *)(ptr), 
                          (unsigned long long *)(ptr),
                          1,    // Target PE
                          1,    // Number of elements            
                          1 );  // Stride                  
  }

  /* perform a barrier */
  xbrtime_barrier();

  printf( "PE=%d: PTR[0]=0x%"PRIu64"\n", 
          xbrtime_mype(), ptr[0]);

  xbrtime_free( ptr );
  xbrtime_close();
  return rtn;
}

/* EOF */
