/*
 * _XBRTIME_UTIL_C_
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

uint32_t xbrtime_decode_pe( int pe );


uint64_t __xbrtime_ltor(uint64_t local_addr, int pe){
  /* Find the remote address corresponding to the local address of a symmetric object on PE*/
  uint64_t base_slot     = 0x00ull;
  uint64_t offset        = 0x00ull;
  uint64_t remote_addr   = 0x00ull;

  if( xbrtime_mype() == pe ){
    /* return the same address block */
    return local_addr;
  }else{
    /* perform the address translation */

#ifdef XBRTIME_DEBUG
    printf( "XBRTIME_DEBUG : PE=%d: Translating local address at pe=%d from 0x%x\n",
            xbrtime_mype(), pe, local_addr );
#endif

    for( int i=0; i<_XBRTIME_MEM_SLOTS_; i++ ){
      if( (local_addr >= __XBRTIME_CONFIG->_MMAP[i].start_addr) &&
          (local_addr < (__XBRTIME_CONFIG->_MMAP[i].start_addr +
                         __XBRTIME_CONFIG->_MMAP[i].size)) ){
        /* found our slot */
        base_slot = (uint64_t)(&__XBRTIME_CONFIG->_MMAP[i].start_addr);

        /* calculate the local offset */
        offset = local_addr - __XBRTIME_CONFIG->_MMAP[i].start_addr;

        remote_addr = __xbrtime_get_remote_alloc(base_slot, xbrtime_decode_pe(pe)) + offset;

#ifdef XBRTIME_DEBUG
        printf( "XBRTIME_DEBUG : PE=%d: REMOTE ADDRESS IN SLOT=%d AT PE=%d IS 0x%x\n",
                i, xbrtime_mype(), pe, remote_addr );
#endif
        return remote_addr;
      }
    }
  }
  /*
   * if we reach this point, there is an error in translation
   * return 0x00ull will cause a user access violation on the
   * memory operation and raise a segmentation fault
   *
   */
  return 0x00ull;
}

int xbrtime_pe_accessible( int pe ){
  if( __XBRTIME_CONFIG == NULL ){
    return 0;
  }
  if( pe > (__XBRTIME_CONFIG->_NPES-1)  || pe < 0){
    return 0;
  }
  return 1;
}

int xbrtime_addr_accessible( const void *addr, int pe ){
  int flag = 0;
  uint64_t remote_start = 0x00ull;
  size_t remote_size  = 0x00ull;
  if( pe > (__XBRTIME_CONFIG->_NPES-1) ){
    return 0;
  }
  /* check to see if the address is in the remote  */
  for( int i=0; i<_XBRTIME_MEM_SLOTS_; i++ ){
    remote_start = __xbrtime_get_remote_alloc( (uint64_t)(&__XBRTIME_CONFIG->_MMAP[i].start_addr), xbrtime_decode_pe(pe) );
    remote_size  = __XBRTIME_CONFIG->_MMAP[i].size;
    if ( (uint64_t)(addr) >= remote_start &&
         (uint64_t)(addr) < (remote_start + remote_size) ){
      flag = 1;
      break;
    }
  }
  if (flag == 0) {
    return 0;
  }
  return 1;
}

uint64_t xbrtime_ptr( const void *dest, int pe ){
  return __xbrtime_ltor( (uint64_t)(dest), pe );
}

uint32_t xbrtime_decode_pe( int pe ){
  uint32_t raw_pe = 0;
  int i=0;

  if( __XBRTIME_CONFIG == NULL ){
    return raw_pe;
  }

  for( i=0; i<__XBRTIME_CONFIG->_NPES; i++ ){
    if( __XBRTIME_CONFIG->_MAP[i]._PHYSICAL == pe ){
      return __XBRTIME_CONFIG->_MAP[i]._NAMESPACE;
    }
  }

  return raw_pe;
}

/* EOF */
