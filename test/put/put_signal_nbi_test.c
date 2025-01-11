/* _PUT_INT_TEST_C_
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
  int i;

  xbrtime_init();
  size_t size = 4;

  int mype = xbrtime_mype();
  int npes = xbrtime_num_pes();
  int pe = (mype + 1) % npes;

  uint64_t *message = malloc(size * sizeof(uint64_t));

  uint64_t *sig_addr = (uint64_t *)xbrtime_malloc( sizeof(uint64_t) );
  sig_addr[0] = 0;

  for (i = 0; i < size; i++) {
    message[i] = mype + i;
  }

  uint64_t *data = (uint64_t *)(xbrtime_malloc( sizeof(uint64_t) * size ));

  if (mype == 0) {
    printf("PE %d: Putting data to PE %d\n", mype, pe);
    xbrtime_uint64_put_signal_nbi(data, message, size, sig_addr, 1, XBRTIME_SIGNAL_SET, pe);
    printf("PE %d: Waiting for data from PE %d\n", mype, pe);
    xbrtime_uint64_wait_until(sig_addr, XBRTIME_CMP_EQ, 1);
  }
  else {
    printf("PE %d: Waiting for data from PE %d\n", mype, pe);
    xbrtime_uint64_wait_until(sig_addr, XBRTIME_CMP_EQ, 1);
    printf("PE %d: Data receive\nd", mype);
    printf("PE %d: Putting data to PE %d\n", mype, pe);
    xbrtime_uint64_put_signal_nbi(data, data, size, sig_addr, 1, XBRTIME_SIGNAL_SET, pe);
  }

  xbrtime_quiet();

  printf("PE %d: Data received, sig_addr = %d\n", mype, sig_addr[0]);

  if ( mype == 1) {
    for (i = 0; i < size; i++) {
      printf("PE %d: data[%d] = %lu\n", mype, i, data[i]);
    }
  }

  free( message );
  xbrtime_free( sig_addr );
  xbrtime_free( data );
  xbrtime_close();
  
  return 0;
}

/* EOF */



