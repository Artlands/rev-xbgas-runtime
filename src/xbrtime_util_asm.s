#
# _XBRTIME_UTIL_ASM_S_
#
# Copyright (C) 2017-2024 Tactical Computing Laboratories, LLC
# All Rights Reserved
# contact@tactcomplabs.com
#
# This file is a part of the XBGAS-RUNTIME package.  For license
# information, see the LICENSE file in the top level directory
# of the distribution.
#

# e10 = contains the physical PE id
# e11 = contains the number of PEs
# e12 = contains the size of the shared memory region
# e13 = contains the starting address of the physical shared memory region
# e14 = contains the starting address of the barrier variable

  .file "xbrtime_util_asm.s"
  .text
  .align 1

  .global __xbrtime_asm_get_id
  .type __xbrtime_asm_get_id, @function
__xbrtime_asm_get_id:
  eaddi a0,e10,0
  ret
  .size __xbrtime_asm_get_id, .-__xbrtime_asm_get_id

  .global __xbrtime_asm_get_npes
  .type __xbrtime_asm_get_npes, @function
__xbrtime_asm_get_npes:
  eaddi a0,e11,0
  ret
  .size __xbrtime_asm_get_npes, .-__xbrtime_asm_get_npes

  .global __xbrtime_asm_get_memsize
  .type __xbrtime_asm_get_memsize, @function
__xbrtime_asm_get_memsize:
  eaddi a0,e12,0
  ret
  .size __xbrtime_asm_get_memsize, .-__xbrtime_asm_get_memsize

  .global __xbrtime_asm_get_startaddr
  .type __xbrtime_asm_get_startaddr, @function
__xbrtime_asm_get_startaddr:
  eaddi a0,e13,0
  ret
  .size __xbrtime_asm_get_startaddr, .-__xbrtime_asm_get_startaddr

  .global __xbrtime_asm_get_barrier_addr
  .type __xbrtime_asm_get_barrier_addr, @function
__xbrtime_asm_get_barrier_addr:
  eaddi a0,e14,0
  ret
  .size __xbrtime_asm_get_barrier_addr, .-__xbrtime_asm_get_barrier_addr

  .globl __xbrtime_asm_fence
  .type __xbrtime_asm_fence, @function
__xbrtime_asm_fence:
  fence.i
  ret
  .size __xbrtime_asm_fence, .-__xbrtime_asm_fence

  .globl __xbrtime_asm_quiet_fence
  .type __xbrtime_asm_quiet_fence, @function
__xbrtime_asm_quiet_fence:
  fence
  ret
  .size __xbrtime_asm_quiet_fence, .-__xbrtime_asm_quiet_fence


  # __xbrtime_get_remote_alloc calling convention
  # - a0 = base address of slot to query from
  # - a1 = remote pe
  .globl __xbrtime_get_remote_alloc
  .type __xbrtime_get_remote_alloc, @function
__xbrtime_get_remote_alloc:
  eaddie e10, a1, 0
  eld a0, 0(a0)
  ret
  .size __xbrtime_get_remote_alloc, .-__xbrtime_get_remote_alloc

  # __xbrtime_remote_touch
  # - a0 = base address of remote barrier variable
  # - a1 = remote pe
  # - a2 = sense
  .globl __xbrtime_remote_touch
  .type __xbrtime_remote_touch, @function
__xbrtime_remote_touch:
  eaddie e10, a1, 0
  esd a2, 0(a0)
  ret
  .size __xbrtime_remote_touch, .-__xbrtime_remote_touch

  # __xbrtime_wait_bulk_comp
  # Check the CSR for bulk completion
  .global __xbrtime_wait_bulk_comp
  .type __xbrtime_wait_bulk_comp, @function
__xbrtime_wait_bulk_comp:
  .wait_bulk_loop:
    csrr t0, 0xca0
    beqz t0, .wait_bulk_loop
    ret
  .size __xbrtime_wait_bulk_comp, .-__xbrtime_wait_bulk_comp
