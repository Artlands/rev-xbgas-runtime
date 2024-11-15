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

// #define _ALLOC_DEBUG_

// base stores the head of the memory block list
void *shbase = NULL;

mem_block *__merge_blocks(mem_block *block, size_t meta) {
  // Merge the block with its next block
  if (block->next && block->next->free) {
    block->free = 1;
    block->size += meta + block->next->size;
    block->next = block->next->next;
    if (block->next) {
      block->next->prev = block;
    }
#ifdef _ALLOC_DEBUG_
  printf("Merge the block with the next block. Merged block Start: %p, Size: %ld", (void *)block, block->size);
#endif
  }
  // Merge the block with its previous block
  if (block->prev && block->prev->free) {
    block->prev->free = 1;
    block->prev->size += meta + block->size;
    block->prev->next = block->next;
    if (block->next) {
      block->next->prev = block->prev;
    }
#ifdef _ALLOC_DEBUG_
  printf("Merge the block with the next block. Merged block Start: %p, Size: %ld", (void *)(block->prev), block->prev->size);
#endif
    return block->prev;
  }
  return block;
}

void __split_block(mem_block *block, size_t size, size_t meta) {
  mem_block *new_block = (mem_block *)((uintptr_t)block + meta + size);
  new_block->free = 1;
  new_block->size = block->size - size - meta;
  new_block->next = block->next;
  new_block->prev = block;

  block->free = 0;
  block->size = size;
  block->next = new_block;
  if (new_block->next) {
    new_block->next->prev = new_block;
  }
#ifdef _ALLOC_DEBUG_
  printf("Split the block. Original block: Start: %p, Size: %ld", (void *)block, block->size);
  printf("----> New block: Start: %p, Size: %ld", (void *)new_block, new_block->size);
#endif
}

mem_block *__find_block(mem_block *base, size_t size) {
  mem_block *current = base;
  while (current && !( current->free && current->size >= size)) {
    current = current->next;
  }
  return current;
}

void *__malloc_align(size_t size, size_t alignment) {
  if (size <= 0) {
    return NULL;
  }
  // Calculate the total size to be allocated from REV system call.
  // The total size includes the requested size, the size of the original pointer 
  // and the size of the aligned memory address, and it is aligned to the alignment.
  size_t total_size = ((size + 2 * sizeof(uintptr_t) - 1)/alignment + 1) * alignment;
  uintptr_t original = (uintptr_t)rev_mmap(0,
                                           total_size,
                                           PROT_READ | PROT_WRITE,
                                           MAP_PRIVATE | MAP_ANONYMOUS,
                                           -1,
                                           0);
  if (original == 0) {
    return NULL;
  }
  // Find the aligned memory address after original
  uintptr_t aligned = (original + 2 * sizeof(uintptr_t) + alignment - 1) & ~(alignment - 1);
  
  // Store the original pointer and size just before the aligned memory
  ((uintptr_t*)aligned)[-2] = original;
  ((uintptr_t*)aligned)[-1] = total_size;

#ifdef _ALLOC_DEBUG_
  printf("Allocate a new segment. Total size: %lu", total_size);
  printf("----> Original pointer: %p, Aligned pointer %p", (void *)original, (void *)aligned);
#endif

  return (void *)aligned;
}

void __free_align(void *ptr, size_t alignment) {
  if (!ptr) {
    return;
  }
  // Call the REV system call to free memory
  rev_munmap((void *)(((uintptr_t*)ptr)[-2]), ((uintptr_t*)ptr)[-1]);

#ifdef _ALLOC_DEBUG_
  printf("Free the memory. Aligned pointer: %p", ptr);
  printf("----> Original pointer: %p", (void *)(((uintptr_t*)ptr)[-2]));
  printf("----> Size: %lu", ((uintptr_t*)ptr)[-1]);
#endif

  return;
}

void *__shmem_malloc_align(size_t size, size_t alignment) {
  if( size <= 0 ) {
    return NULL;
  }
  if (!__XBRTIME_CONFIG) {
    return NULL;
  }
  if (__XBRTIME_CONFIG->_START_ADDR == 0x00ull) {
    return NULL;
  }

  mem_block *block;

  // Align the size to achieve proper alignment
  size_t aligned_size = ( (size - 1)/alignment + 1 ) * alignment;
  size_t total_size = _ALIGNED_META_ + aligned_size;

  if( !shbase ) {
    // First time allocation, initialize a new block from the heap.
    void *shbase_original = (void *)(__XBRTIME_CONFIG->_START_ADDR);
    size_t shsize = __XBRTIME_CONFIG->_MEMSIZE;
    size_t shsize_aligned = ( shsize/alignment ) * alignment;

    // Align the base original address to the alignment
    shbase = (void *)( ((uintptr_t)shbase_original + alignment - 1) & ~(alignment - 1) );
    block = (mem_block *)(shbase);
    block->free = 1;
    block->size = shsize_aligned - _ALIGNED_META_;
    block->next = NULL;
    block->prev = NULL;
    if( block->size > total_size ){
      __split_block(block, aligned_size, _ALIGNED_META_);
    } else if (block->size == total_size) {
      block->free = 0;
    } else {
      return NULL;
    }
    return (void *)((uintptr_t)block + _ALIGNED_META_);
  } else {
    // Search the block list
    block = __find_block(shbase, total_size);
    if (!block) {
      return NULL;
    } else {
      if( block->size > total_size ){
        __split_block(block, aligned_size, _ALIGNED_META_);
      } else {
        block->free = 0;
      }
      return (void *)((uintptr_t)block + _ALIGNED_META_);
    }
  }
}

void __shmem_free(void *ptr) {
  if( !ptr ) {
    return;
  }
  if (!__XBRTIME_CONFIG) {
    return;
  }
  if (__XBRTIME_CONFIG->_START_ADDR == 0x00ull) {
    return;
  }

  // Find the block corresponding to the pointer
  mem_block *block = (mem_block *)((uintptr_t)ptr - _ALIGNED_META_);

  // Mark the block as free
  block->free = 1;

  // Merge the block with the neighbor blocks, block will be updated to the start of the merged block
  block = __merge_blocks(block, _ALIGNED_META_);

  return;
}

void *__xbrtime_shared_malloc( size_t size, size_t alignment ){
  if (size <= 0) {
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
  ptr = __shmem_malloc_align(size, alignment);;
  if( ptr == NULL ){
    return NULL;
  }

  /* memory is good, register the block */
#ifdef XBRTIME_DEBUG
  printf( "\033[32mXBRTIME_DEBUG :\033[0m PE=%d: ALLOCATING MEMORY IN SLOT=%d AT ADDRESS 0x%"PRIx64", SIZE %d",
          xbrtime_mype(), slot, ptr, size );
#endif

  __XBRTIME_CONFIG->_MMAP[slot].size = size;
  __XBRTIME_CONFIG->_MMAP[slot].start_addr = (uintptr_t)(ptr);
  return ptr;
}

void __xbrtime_shared_free(void *ptr){
  uintptr_t mem = (uintptr_t)(ptr);
  int i = 0;

  /* walk the allocated blocks and attempt to free the allocation */
  for( i=0; i<_XBRTIME_MEM_SLOTS_; i++ ){
    if( (mem >= __XBRTIME_CONFIG->_MMAP[i].start_addr) &&
        (mem < (__XBRTIME_CONFIG->_MMAP[i].start_addr+
                __XBRTIME_CONFIG->_MMAP[i].size)) ){
      /* found the allocation */
      __shmem_free(ptr);
      __XBRTIME_CONFIG->_MMAP[i].start_addr = 0x00ull;
      __XBRTIME_CONFIG->_MMAP[i].size = 0;
      return ;
    }
  }
}

void* malloc(size_t size) {
  return __malloc_align(size, _DEFAULT_ALIGNMENT_);
}

void *realloc(void* ptr, size_t new_size){
  void *new_ptr = NULL;
  size_t old_size = 0;

  if( ptr == NULL ){
    return malloc(new_size);
  }

  if( new_size == 0 ){
    free(ptr);
    return NULL;
  }

  old_size = ((uintptr_t*)ptr)[-1];
  if( old_size >= new_size ){
    return ptr;
  }

  new_ptr = __malloc_align(new_size, _DEFAULT_ALIGNMENT_);
  if( new_ptr == NULL ){
    return NULL;
  }

  // Copy the old data to the new location
  for( size_t i=0; i<old_size; i++ ){
    ((char*)new_ptr)[i] = ((char*)ptr)[i];
  }

  // Free the old memory
  __free_align(ptr, _DEFAULT_ALIGNMENT_);

  return new_ptr;
}

void free(void *ptr) {
  __free_align(ptr, _DEFAULT_ALIGNMENT_);
}

void *xbrtime_malloc( size_t size ){
  void *ptr = NULL;

  if( __XBRTIME_CONFIG == NULL ){
    return NULL;
  }

  if( size == 0 ){
    return NULL;
  }

  ptr = __xbrtime_shared_malloc( size, _DEFAULT_ALIGNMENT_ );
  return ptr;
}

void xbrtime_free( void *ptr ){
  if( ptr == NULL ){
    return;
  }
  
  if( __XBRTIME_CONFIG == NULL ){
    return;
  }
  
  if( __XBRTIME_CONFIG->_MMAP == NULL ){
    return;
  }
  __xbrtime_shared_free(ptr);
}

void *xbrtime_realloc(void *ptr, size_t new_size){
  void *new_ptr = NULL;
  size_t old_size = 0;
  mem_block *block = (mem_block *)((uintptr_t)ptr - _ALIGNED_META_);

  if( ptr == NULL ){
    return xbrtime_malloc(new_size);
  }

  if( new_size == 0 ){
    xbrtime_free(ptr);
    return NULL;
  }

  old_size = block->size;
  if( old_size >= new_size ){
#ifdef _ALLOC_DEBUG_
  printf("Old size is greater than or equal to new size. Old size: %ld, New size: %ld", old_size, new_size);
#endif
    return ptr;
  }

  new_ptr = __xbrtime_shared_malloc(new_size, _DEFAULT_ALIGNMENT_);
  if( new_ptr == NULL ){
    return NULL;
  }

#ifdef _ALLOC_DEBUG_
  printf("Old size is less than new size. Old size: %ld, New size: %ld", old_size, new_size);
  printf("Allocate a new block. Address: %p, Size: %ld", new_ptr, new_size);
#endif

  // Copy the old data to the new location
  for( size_t i=0; i<old_size; i++ ){
    ((char*)new_ptr)[i] = ((char*)ptr)[i];
  }

  // Free the old memory
  __xbrtime_shared_free(ptr);

  return new_ptr;
}

void *xbrtime_align(size_t alignment, size_t size ){
  void *ptr = NULL;

  if( __XBRTIME_CONFIG == NULL ){
    return NULL;
  }

  // If alignment is not power of 2, also return NULL
  if( ( size == 0 ) || (alignment & (alignment - 1)) != 0 ) {
    return NULL;
  }

  ptr = __xbrtime_shared_malloc( size, alignment );
  return ptr;
}

/* EOF */
