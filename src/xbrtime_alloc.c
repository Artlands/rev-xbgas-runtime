/*
 * _XBRTIME_ALLOC_C_
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
#include <inttypes.h>

/* ------------------------------------------------- FUNCTION PROTOTYPES */
void __xbrtime_asm_quiet_fence();

void *__xbrtime_shared_malloc( size_t sz ){
  if (sz <= 0) {
    return NULL;
  }
  void *ptr = NULL;
  int slot  = -1;

  /* find an open slot */
  for( int i=0; i<_XBRTIME_MEM_SLOTS_; i++ ){
    if( __XBRTIME_CONFIG->_MMAP[i].size == 0 ){
      slot = i;
      break;
    }
  }

  /* no open slots */
  if( slot == -1 ){
    return NULL;
  }

  /* attempt to create an allocation on the pre-allocated heap*/
  ptr = shmalloc( sz );
  if( ptr == NULL ){
    return NULL;
  }

  /* memory is good, register the block */
#ifdef XBRTIME_DEBUG
  printf( "\033[32mXBRTIME_DEBUG :\033[0m PE=%d: ALLOCATING MEMORY IN SLOT=%d AT ADDRESS 0x%"PRIx64", SIZE %d",
          xbrtime_mype(), slot, ptr, sz );
#endif

  __XBRTIME_CONFIG->_MMAP[slot].size = sz;
  __XBRTIME_CONFIG->_MMAP[slot].start_addr = (uint64_t)(ptr);
  return ptr;
}

void __xbrtime_shared_free(void *ptr){
  uint64_t mem = (uint64_t)(ptr);
  int i = 0;

  /* walk the allocated blocks and attempt to free the allocation */
  for( i=0; i<_XBRTIME_MEM_SLOTS_; i++ ){
    if( (mem >= __XBRTIME_CONFIG->_MMAP[i].start_addr) &&
        (mem < (__XBRTIME_CONFIG->_MMAP[i].start_addr+
                __XBRTIME_CONFIG->_MMAP[i].size)) ){
      /* found the allocation */
      shfree( ptr );
      __XBRTIME_CONFIG->_MMAP[i].start_addr = 0x00ull;
      __XBRTIME_CONFIG->_MMAP[i].size = 0;
      return ;
    }
  }
}

extern void *xbrtime_malloc( size_t sz ){
  void *ptr = NULL;

  /* sanity check */
  if( sz == 0 ){
    return NULL;
  }else if( __XBRTIME_CONFIG == NULL ){
    return NULL;
  }

  ptr = __xbrtime_shared_malloc( sz );
  __xbrtime_asm_quiet_fence();

  return ptr;
}

extern void xbrtime_free( void *ptr ){
  if( ptr == NULL ){
    return ;
  }else if( __XBRTIME_CONFIG == NULL ){
    return ;
  }else if( __XBRTIME_CONFIG->_MMAP == NULL ){
    return ;
  }
  __xbrtime_shared_free(ptr);
  __xbrtime_asm_quiet_fence();
}
