/*
 * _XBRTIME_BARRIER_ALL_C_
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
#define SENSE __XBRTIME_CONFIG->_SENSE

// #define _BARRIER_DEBUG_

/* ------------------------------------------------- FUNCTION PROTOTYPES */
void __xbrtime_asm_fence();
void __xbrtime_asm_quiet_fence();
void __xbrtime_remote_touch( uint64_t addr, uint64_t target, uint64_t sense );
uint32_t xbrtime_decode_pe( int pe );

extern void xbrtime_barrier_all(){

	int64_t 	i 							= 0; 
	int64_t		stride 					= 1;
  uint64_t 	target 					= 0x00ull;
  uint64_t 	addr 						= 0x00ull;
	int64_t	 	num_pe 					= xbrtime_num_pes();
	
  /* sanity check */
  if( num_pe == 1 ){
    return ;
  }
	
	/*Get the total iterations */
	int64_t  mype   = xbrtime_mype();
	int64_t	 iter   = (int64_t)(log(num_pe)/log(2));
	if (iter < log(num_pe)/log(2))
		iter++;
  
	// Comment out the heavy fence. This causes the reduction tests hang.
  /* force a heavy fence */
  // __xbrtime_asm_fence();

	while(i < iter){
  	/* derive the correct target pe */
		target 	= (mype + stride)%num_pe; 

#ifdef _BARRIER_DEBUG_
  	printf( "XBRTIME_DEBUG : PE=%d: Barrier target = %d\n", xbrtime_mype(),
          (int)(target) );
#endif

  	target 	= (uint64_t)(xbrtime_decode_pe((int)(target)));
  	addr 		= (uint64_t)(&__XBRTIME_CONFIG->_BARRIER[SENSE*10+i]);

#ifdef _BARRIER_DEBUG_
  	printf( "XBRTIME_DEBUG : PE=%d: Touching remote address on physical target = %d\n",
          xbrtime_mype(),
          (int)(target) );
#endif

  	__xbrtime_remote_touch( addr, target, stride);	

#ifdef _BARRIER_DEBUG_
  	printf( "XBRTIME_DEBUG : PE=%d: Success touching remote address\n", xbrtime_mype() );
#endif

  	/* spinwait on local value */
 		while( __XBRTIME_CONFIG->_BARRIER[SENSE*10+i] != stride ){
#ifdef XBRTIME_DEBUG
			printf("XBRTIME_DEBUG : PE = %d, SENSE = %ld, Local barrier = 0x%lx\n",xbrtime_mype(), SENSE, __XBRTIME_CONFIG->_BARRIER[SENSE]);
#endif
		}

		stride *= 2;
		i++;
	}

  /* switch the sense */
	for (i = 0; i < iter; i++)
  	__XBRTIME_CONFIG->_BARRIER[SENSE*10+i] = 0xdeadbeefull;
	// Flip the Sense
  SENSE = 1 - SENSE;

#ifdef _BARRIER_DEBUG_
  printf( "XBRTIME_DEBUG : PE=%d: Barrier complete\n", xbrtime_mype() );
#endif
}

extern void xbrtime_fence(){
	__xbrtime_asm_fence();
}

extern void xbrtime_quiet(){
	__xbrtime_asm_quiet_fence();
}


/* EOF */
