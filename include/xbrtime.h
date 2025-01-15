/*
 * _XBRTIME_H_
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

/*!   \file xbrtime.h
      \brief XBGAS Runtime Top-Level Header File

      The XBGAS Runtime provides C/CXX level function interfaces
      for applications to conveniently utilize the shared memory
      capabilities present in the xBGAS extension to the RISC-V
      specification
*/

#ifndef _XBRTIME_H_
#define _XBRTIME_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>
#include <inttypes.h>
#include "syscalls.h"

/* ---------------------------------------- REQUIRED HEADERS */
#include "xbrtime_types.h"
#include "xbrtime_api.h"
#include "xbrtime_alloc.h"
#include "xbrtime_version.h"
#include "xbrtime_macros.h"
#include "xbrtime_collectives.h"
#include "xbrtime_atomics.h"
#include "xbrtime_wait.h"
#include "xbrtime_lock.h"
#include "xbrtime_test.h"
#include "xbrtime_print.h"
// #define printf rev_fast_printf

enum xbgas_cmp_ops {
    XBRTIME_CMP_EQ,
    XBRTIME_CMP_NE,
    XBRTIME_CMP_GT,
    XBRTIME_CMP_LE,
    XBRTIME_CMP_LT,
    XBRTIME_CMP_GE
};

enum xbgas_signal_ops {
    XBRTIME_SIGNAL_SET,
    XBRTIME_SIGNAL_ADD,
};

/* ---------------------------------------- FUNCTION PROTOTYPES */

/*!   \fn int xbrtime_init()
      \brief Initializes the XBGAS Runtime environment
      \return 0 on success, nonzero otherwise
*/
extern int xbrtime_init();

/*!   \fn void xbrtime_close()
      \brief Closes the XBGAS Runtime environment
      \return void
*/
extern void xbrtime_close();

/*!   \fn int xbrtime_pe_accessible( int pe )
      \brief Checks to see whether a pe is accessible via the data transfer routines
      \param pe is the target processing element
      \return 1 on success, 0 otherwise
*/
extern int xbrtime_pe_accessible( int pe );

/*!   \fn int xbrtime_addr_accessible( const void *addr, int pe )
      \brief Checks to see whether the address on the target pe can be reached
      \param addr is a pointer to a valid address
      \param pe is the target processing element
      \return 1 on success, 0 otherwise
*/
extern int xbrtime_addr_accessible( const void *addr, int pe );

/*!   \fn uint64_t xbrtime_ptr( const void *dest, int pe )
      \brief Returns the address of a symmetric data object on the specified PE.
      \param dest is the symmetric address of the remotely accessible data object to be referenced.
      \param pe is an integer that indicates the PE number on which dest is to be accessed.
      \return The address of an remotely accessible dest data object is returned when it can be accessed using memory loads and stores. 
      Otherwise, 0x00ull is returned.
*/
extern uint64_t xbrtime_ptr( const void *dest, int pe );

/*!   \fn void *xbrtime_malloc( size_t sz )
      \brief Allocates a block of contiguous shared memory of minimum size, 'sz'
      \param sz is the minimum size of the allocated block
      \return Valid pointer on success, NULL otherwise
*/
extern void *xbrtime_malloc( size_t sz );

/*!   \fn void xbrtime_free( void *ptr )
      \brief Free's a target memory block starting at ptr
      \param *ptr is a valid base pointer to an allocated block
      \return Void
*/
extern void xbrtime_free( void *ptr );

/*!   \fn int xbrtime_mype()
      \brief Returns the logical PE number of the calling entity
      \return Logical PE on success, nonzero otherwise
*/
extern int xbrtime_mype();


/*!   \fn int xbrtime_num_pes()
      \brief Returns the total number of configured PEs
      \return Total PEs on success, nonzero otherwise
*/
extern int xbrtime_num_pes();

/*!   \fn void xbrtime_barrier_all()
      \brief Performs a global barrier operation of all configured PEs
      \return Void
*/
extern void xbrtime_barrier_all();

/*!   \fn void xbrtime_fence()
      \brief Ensures ordering of delivery of operations on symmetric data objects.
      \return Void
*/
extern void xbrtime_fence();

/*!   \fn void xbrtime_quiet()
      \brief Waits for completion of outstanding operations on symmetric data objects issued by a PE.
      \return Void
*/
extern void xbrtime_quiet();



#ifdef __cplusplus
}
#endif  /* extern "C" */

#endif /* _XBRTIME_H_ */

/* EOF */
