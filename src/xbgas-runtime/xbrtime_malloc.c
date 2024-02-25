// See LICENSE for license details.
#include "xbrtime.h"

void *malloc(size_t size) {
  if( size <= 0 ) {
    return NULL;
  }

  // Align size to include the metadata structure and achieve proper alignment
  size_t total_size = align8(BLOCK_SIZE + size);

  // Request memory from the REV system call
  void *block = (void *)rev_mmap(0,
                                 total_size,
                                 PROT_READ | PROT_WRITE,
                                 MAP_PRIVATE | MAP_ANONYMOUS,
                                 -1,
                                 0);
  
  // Initialize the block metadata
  mem_block *block_header = (mem_block *)block;
  // Since the memory allocation is actually managed by the REV system call,
  // we only need to record the size of the block that is used when freeing the block
  block_header->size = size;

  // printf("Malloc total_size: %lu at %p\n", total_size, block);
  // Return the pointer to the user data
  return (void *)((char *)block + BLOCK_SIZE);
}

void free(void *ptr) {
  if( !ptr ) {
    return;
  }

  // Get the block metadata
  mem_block *block_header = (mem_block *)((char *)ptr - BLOCK_SIZE);

  // Total size of the block
  size_t total_size = align8(BLOCK_SIZE + block_header->size);

  // Free the block using the REV system call
  rev_munmap((void *)block_header, total_size);
}