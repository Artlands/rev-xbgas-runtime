/*
 * _XBRTIME_ALLOC_H_
 *
 * Copyright (C) 2017-2025 Tactical Computing Laboratories, LLC
 * All Rights Reserved
 * contact@tactcomplabs.com
 *
 * This file is a part of the XBGAS-RUNTIME package.  For license
 * information, see the LICENSE file in the top level directory
 * of the distribution.
 *
 */

#ifndef _XBRTIME_ALLOC_H_
#define _XBRTIME_ALLOC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

typedef struct mem_block
{ 
  // The order of the members should not be changed
  int free;
  size_t size;
  struct mem_block *next;
  struct mem_block *prev;
} mem_block;

typedef struct _XBRTIME_MEM_T{
  uint64_t start_addr;
  size_t size;
}XBRTIME_MEM_T;

#define _DEFAULT_ALIGNMENT_ 8
#define _MEM_META_SIZE_  32

extern void *malloc(size_t size);
extern void *realloc(void* ptr, size_t new_size);
extern void free(void *ptr);

// Malloc on symmetric heap
extern void *xbrtime_malloc(size_t size);
extern void xbrtime_free(void *ptr);
extern void *xbrtime_realloc(void *ptr, size_t new_size);
extern void *xbrtime_align( size_t alignment, size_t size );
extern void *xbrtime_calloc(size_t count, size_t size);

#ifdef __cplusplus
}
#endif  /* extern "C" */

#endif /* _XBRTIME_ALLOC_H_ */

/* EOF */
