/*
 * _XBRTIME_INIT_C_
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

/* ------------------------------------------------- GLOBALS */
XBRTIME_DATA *__XBRTIME_CONFIG;

/* ------------------------------------------------- FUNCTION PROTOTYPES */
int      __xbrtime_asm_get_id();
int      __xbrtime_asm_get_npes();
size_t   __xbrtime_asm_get_memsize();
uint64_t __xbrtime_asm_get_startaddr();
uint64_t __xbrtime_asm_get_barrier_addr();
void     __xbrtime_asm_fence();

extern void xbrtime_close(){
  int i = 0;

  /* initiate a barrier */
  xbrtime_barrier();

  if( __XBRTIME_CONFIG != NULL ){
    /* hard fence */
    __xbrtime_asm_fence();

    /* free all the remaining shared blocks */
    for( i=0; i<_XBRTIME_MEM_SLOTS_; i++ ){
      if( __XBRTIME_CONFIG->_MMAP[i].size != 0 ){
        xbrtime_free((void *)(__XBRTIME_CONFIG->_MMAP[i].start_addr));
      }
    }

    if( __XBRTIME_CONFIG->_MAP != NULL ){
      free( __XBRTIME_CONFIG->_MAP );
      __XBRTIME_CONFIG->_MAP = NULL;
    }

    free( __XBRTIME_CONFIG );
  }
}

int xbrtime_init(){

  /* vars */
  int i = 0;

  /* allocate the structure in the local heap */
  __XBRTIME_CONFIG = NULL;
  __XBRTIME_CONFIG = malloc( sizeof( XBRTIME_DATA ) );
  if( __XBRTIME_CONFIG == NULL ){
    return -1;
  }

  __XBRTIME_CONFIG->_ID         = (int)(__xbrtime_asm_get_id());
  __XBRTIME_CONFIG->_NPES       = (int)(__xbrtime_asm_get_npes());
  __XBRTIME_CONFIG->_MEMSIZE    = (int)(__xbrtime_asm_get_memsize());
  __XBRTIME_CONFIG->_START_ADDR = (uint64_t)(__xbrtime_asm_get_startaddr());
  __XBRTIME_CONFIG->_SENSE      = 0x01ull;
  __XBRTIME_CONFIG->_BARRIER 		= (uint64_t*)(__xbrtime_asm_get_barrier_addr());
  __XBRTIME_CONFIG->_MMAP       = malloc(sizeof(XBRTIME_MEM_T) * _XBRTIME_MEM_SLOTS_);


#ifdef XBRTIME_DEBUG
  printf( "\033[32mXBRTIME_DEBUG :\033[0m PE = %d, NPES = %d, MEMSIZE = %d, START_ADDR = 0x%lx, BARRIER_ADDR = 0x%lx\n",
         __XBRTIME_CONFIG->_ID,
         __XBRTIME_CONFIG->_NPES,
         __XBRTIME_CONFIG->_MEMSIZE,
         __XBRTIME_CONFIG->_START_ADDR,
         __XBRTIME_CONFIG->_BARRIER);
#endif

  /* initialize the barrier */
	// MAX_PE_NUM = 1024, thus, MAX_Barrier buffer space = log2^1024 = 10
	for( i = 0; i < 10; i++){
  	__XBRTIME_CONFIG->_BARRIER[i] 		= (uint64_t)(0xfffffffffull);
  	__XBRTIME_CONFIG->_BARRIER[10+i] 	= (uint64_t)(0xaaaaaaaaaull);
	}

#ifdef XBRTIME_DEBUG
  printf("\033[32mXBRTIME_DEBUG :\033[0m PE:%d----BARRIER[O] = 0x%lx\n", __XBRTIME_CONFIG->_ID, __XBRTIME_CONFIG->_BARRIER[0]);
	printf("\033[32mXBRTIME_DEBUG :\033[0m PE:%d----BARRIER[11] = 0x%lx\n", __XBRTIME_CONFIG->_ID, __XBRTIME_CONFIG->_BARRIER[11]);
#endif

  /* too many total PEs */
  if( __XBRTIME_CONFIG->_NPES > __XBRTIME_MAX_PE ){
    free( __XBRTIME_CONFIG );
    return -1;
  }

  /* init the pe mapping block */
  __XBRTIME_CONFIG->_MAP = malloc( sizeof( XBRTIME_PE_MAP ) *
                                   __XBRTIME_CONFIG->_NPES );
  if( __XBRTIME_CONFIG->_MAP == NULL ){
    free( __XBRTIME_CONFIG );
    return -1;
  }

  /* init the memory allocation slots */
  for( i=0;i<_XBRTIME_MEM_SLOTS_; i++ ){
    __XBRTIME_CONFIG->_MMAP[i].start_addr = 0x00ull;
    __XBRTIME_CONFIG->_MMAP[i].size       = 0;
  }

  /* init the PE mapping structure */
  for( i=0; i<__XBRTIME_CONFIG->_NPES; i++ ){
    __XBRTIME_CONFIG->_MAP[i]._LOGICAL   = i;
    __XBRTIME_CONFIG->_MAP[i]._PHYSICAL  = i+1;
  }

  return 0;
}

extern int xbrtime_mype(){
  if( __XBRTIME_CONFIG == NULL ){
    return -1;
  }
  return __XBRTIME_CONFIG->_ID;
}

extern int xbrtime_num_pes(){
  if( __XBRTIME_CONFIG == NULL ){
    return -1;
  }
  return __XBRTIME_CONFIG->_NPES;
}

/* EOF */
