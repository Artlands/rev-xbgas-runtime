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
#define PAGE_SIZE 4096
#define MAX_SEGMENTS 1024

typedef struct mem_block
{ 
  // The order of the members should not be changed
  int free;
  size_t size;
  struct mem_block *next;
  struct mem_block *prev;
} mem_block;

typedef struct mem_segment
{
  uint64_t start;
  uint64_t end;
} mem_segment;

#define BLOCK_SIZE sizeof(mem_block)

void* malloc(size_t size);
void free(void *ptr);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _XBRTIME_MALLOC_H_ */