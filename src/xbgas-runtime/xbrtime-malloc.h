/*
 * _XBRTIME_MALLOC_H_
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

/*!   \file xbrtime-malloc.h
      \brief XBGAS Runtime Malloc Header File

      The XBGAS Runtime provides C/CXX level function interfaces
      for applications to conveniently utilize the shared memory
      capabilities present in the xBGAS extension to the RISC-V
      specification
*/

#ifndef _XBRTIME_MALLOC_H_
#define _XBRTIME_MALLOC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include "syscalls.h"

#define align8(x) (((((x)-1) >> 3) << 3) + 8)

typedef struct mem_block
{
  size_t size;
} mem_block;

#define BLOCK_SIZE sizeof(mem_block)

void* malloc(size_t size);
void free(void *ptr);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _XBRTIME_MALLOC_H_ */