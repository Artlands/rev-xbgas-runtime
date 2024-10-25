#
# _XBRTIME_ATOMICS_ASM_S_
#
# Copyright (C) 2017-2024 Tactical Computing Laboratories, LLC
# All Rights Reserved
# contact@tactcomplabs.com
#
# This file is a part of the XBGAS-RUNTIME package.  For license
# information, see the LICENSE file in the top level directory
# of the distribution.
#

  .file "xbrtime_atomics_asm.s"
  .text
  .align 1

  #---------------------------------------------------
  # xBGAS ASM Atomic functions are formatted as follows:
  # __xbrtime_atomic_FUNC_OPERAND
  #   where,
  #   - FUNC is one of:
  #     - swap = swap
  #     - add = integer add
  #     - band = bitwise AND
  #     - bor = bitwise OR
  #     - bxor = bitwise XOR
  #     - max = signed integer maximum
  #     - min = signed integer minimum
  #     - maxu = unsigned integer maximum
  #     - minu = unsigned integer minimum
  #     - compare_swap = compare and swap (implemented via lr and sc)
  #   - OPERAND is one of:
  #     - u4 = unsigned four bytes
  #     - s4 = signed four bytes
  #     - u8 = unsigned eight bytes
  #     - s8 = signed eight bytes
  #---------------------------------------------------

    .global __xbrtime_atomic_add_4
    .type __xbrtime_atomic_add_4, @function
  __xbrtime_atomic_add_4:
    eaddie e10, a2, 0
    eamoadd.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_add_4, .-__xbrtime_atomic_add_4

    #---------------------------------------------------

    .global __xbrtime_atomic_add_8
    .type __xbrtime_atomic_add_8, @function
  __xbrtime_atomic_add_8:
    eaddie e10, a2, 0
    eamoadd.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_add_8, .-__xbrtime_atomic_add_8

    #---------------------------------------------------

    .global __xbrtime_atomic_band_4
    .type __xbrtime_atomic_band_4, @function
  __xbrtime_atomic_band_4:
    eaddie e10, a2, 0
    eamoand.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_band_4, .-__xbrtime_atomic_band_4

    #---------------------------------------------------

    .global __xbrtime_atomic_band_8
    .type __xbrtime_atomic_band_8, @function
  __xbrtime_atomic_band_8:
    eaddie e10, a2, 0
    eamoand.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_band_8, .-__xbrtime_atomic_band_8

    #---------------------------------------------------

    .global __xbrtime_atomic_bor_4
    .type __xbrtime_atomic_bor_4, @function
  __xbrtime_atomic_bor_4:
    eaddie e10, a2, 0
    eamoor.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_bor_4, .-__xbrtime_atomic_bor_4

    #---------------------------------------------------

    .global __xbrtime_atomic_bor_8
    .type __xbrtime_atomic_bor_8, @function
  __xbrtime_atomic_bor_8:
    eaddie e10, a2, 0
    eamoor.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_bor_8, .-__xbrtime_atomic_bor_8

    #---------------------------------------------------

    .global __xbrtime_atomic_bxor_4
    .type __xbrtime_atomic_bxor_4, @function
  __xbrtime_atomic_bxor_4:
    eaddie e10, a2, 0
    eamoxor.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_bxor_4, .-__xbrtime_atomic_bxor_4

    #---------------------------------------------------

    .global __xbrtime_atomic_bxor_8
    .type __xbrtime_atomic_bxor_8, @function
  __xbrtime_atomic_bxor_8:
    eaddie e10, a2, 0
    eamoxor.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_bxor_8, .-__xbrtime_atomic_bxor_8

    #---------------------------------------------------

    .global __xbrtime_atomic_min_4
    .type __xbrtime_atomic_min_4, @function
  __xbrtime_atomic_min_4:
    eaddie e10, a2, 0
    eamominu.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_min_4, .-__xbrtime_atomic_min_4

    #---------------------------------------------------

    .global __xbrtime_atomic_min_8
    .type __xbrtime_atomic_min_8, @function
  __xbrtime_atomic_min_8:
    eaddie e10, a2, 0
    eamominu.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_min_8, .-__xbrtime_atomic_min_8

    #---------------------------------------------------

    .global __xbrtime_atomic_max_4
    .type __xbrtime_atomic_max_4, @function
  __xbrtime_atomic_max_4:
    eaddie e10, a2, 0
    eamomaxu.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_max_4, .-__xbrtime_atomic_max_4

    #---------------------------------------------------

    .global __xbrtime_atomic_max_8
    .type __xbrtime_atomic_max_8, @function
    __xbrtime_atomic_max_8:
    eaddie e10, a2, 0
    eamomaxu.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_max_8, .-__xbrtime_atomic_max_8

    #---------------------------------------------------

    .global __xbrtime_atomic_fetch_4
    .type __xbrtime_atomic_fetch_4, @function
  __xbrtime_atomic_fetch_4:
    eaddie e10, a1, 0
    eamoadd.w a0, x0, (a0)
    ret
    .size __xbrtime_atomic_fetch_4, .-__xbrtime_atomic_fetch_4

     #---------------------------------------------------

    .global __xbrtime_atomic_fetch_8
    .type __xbrtime_atomic_fetch_8, @function
  __xbrtime_atomic_fetch_8:
    eaddie e10, a1, 0
    eamoadd.d a0, x0, (a0)
    ret
    .size __xbrtime_atomic_fetch_8, .-__xbrtime_atomic_fetch_8

    #---------------------------------------------------

    .global __xbrtime_atomic_set_4
    .type __xbrtime_atomic_set_4, @function
  __xbrtime_atomic_set_4:
    eaddie e10, a2, 0
    eamoswap.w x0, a1, (a0)
    ret
    .size __xbrtime_atomic_set_4, .-__xbrtime_atomic_set_4

     #---------------------------------------------------

    .global __xbrtime_atomic_set_8
    .type __xbrtime_atomic_set_8, @function
  __xbrtime_atomic_set_8:
    eaddie e10, a2, 0
    eamoswap.d x0, a1, (a0)
    ret
    .size __xbrtime_atomic_set_8, .-__xbrtime_atomic_set_8

    #---------------------------------------------------

    .global __xbrtime_atomic_compare_swap_4
    .type __xbrtime_atomic_compare_swap_4, @function
  __xbrtime_atomic_compare_swap_4:
    eaddie e10, a3, 0
    elr.w t0, (a0)             # Load original value
    bne t0, a1, _cas_fail_4    # Doesn't match, so fail
    esc.w x0, a2, (a0)         # Update
    mv a0, t0                  # Move the returned value to the return register
    ret
  _cas_fail_4:
    esc.w x0, t0, (a0)         # Write back the original value to release the lock
    mv a0, t0                  # Move the returned value to the return register
    ret                        # Return
    .size __xbrtime_atomic_compare_swap_4, .-__xbrtime_atomic_compare_swap_4

    #---------------------------------------------------

    .global __xbrtime_atomic_compare_swap_8
    .type __xbrtime_atomic_compare_swap_8, @function
  __xbrtime_atomic_compare_swap_8:
    eaddie e10, a3, 0
    elr.d t0, (a0)             # Load original value
    bne t0, a1, _cas_fail_8    # Doesn't match, so fail
    esc.d x0, a2, (a0)         # Update
    mv a0, t0                  # Move the returned value to the return register
    ret
  _cas_fail_8:
    esc.d x0, t0, (a0)         # Write back the original value to release the lock
    mv a0, t0                  # Move the returned value to the return register
    ret                        # Return
    .size __xbrtime_atomic_compare_swap_8, .-__xbrtime_atomic_compare_swap_8

    #---------------------------------------------------

    .global __xbrtime_atomic_swap_4
    .type __xbrtime_atomic_swap_4, @function
  __xbrtime_atomic_swap_4:
    eaddie e10, a2, 0
    eamoswap.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_swap_4, .-__xbrtime_atomic_swap_4

     #---------------------------------------------------

    .global __xbrtime_atomic_swap_8
    .type __xbrtime_atomic_swap_8, @function
  __xbrtime_atomic_swap_8:
    eaddie e10, a2, 0
    eamoswap.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_swap_8, .-__xbrtime_atomic_swap_8

    #---------------------------------------------------

    .global __xbrtime_atomic_fetch_inc_4
    .type __xbrtime_atomic_fetch_inc_4, @function
  __xbrtime_atomic_fetch_inc_4:
    eaddie e10, a1, 0
    li t0, 1                    # Load the immediate value 1 into register t0
    eamoadd.w a0, t0, (a0)
    ret
    .size __xbrtime_atomic_fetch_inc_4, .-__xbrtime_atomic_fetch_inc_4

     #---------------------------------------------------

    .global __xbrtime_atomic_fetch_inc_8
    .type __xbrtime_atomic_fetch_inc_8, @function
  __xbrtime_atomic_fetch_inc_8:
    eaddie e10, a1, 0
    li t0, 1                    # Load the immediate value 1 into register t0
    eamoadd.d a0, t0, (a0)
    ret
    .size __xbrtime_atomic_fetch_inc_8, .-__xbrtime_atomic_fetch_inc_8

    #---------------------------------------------------

    .global __xbrtime_atomic_inc_4
    .type __xbrtime_atomic_inc_4, @function
  __xbrtime_atomic_inc_4:
    eaddie e10, a1, 0
    li t0, 1                    # Load the immediate value 1 into register t0
    eamoadd.w x0, t0, (a0)
    ret
    .size __xbrtime_atomic_inc_4, .-__xbrtime_atomic_inc_4

     #---------------------------------------------------

    .global __xbrtime_atomic_inc_8
    .type __xbrtime_atomic_inc_8, @function
  __xbrtime_atomic_inc_8:
    eaddie e10, a1, 0
    li t0, 1                    # Load the immediate value 1 into register t0
    eamoadd.d x0, t0, (a0)
    ret
    .size __xbrtime_atomic_inc_8, .-__xbrtime_atomic_inc_8

    #---------------------------------------------------

    .global __xbrtime_atomic_fetch_add_4
    .type __xbrtime_atomic_fetch_add_4, @function
  __xbrtime_atomic_fetch_add_4:
    eaddie e10, a2, 0
    eamoadd.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_fetch_add_4, .-__xbrtime_atomic_fetch_add_4

     #---------------------------------------------------

    .global __xbrtime_atomic_fetch_add_8
    .type __xbrtime_atomic_fetch_add_8, @function
  __xbrtime_atomic_fetch_add_8:
    eaddie e10, a2, 0
    eamoadd.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_fetch_add_8, .-__xbrtime_atomic_fetch_add_8

    #---------------------------------------------------

    .global __xbrtime_atomic_fetch_and_4
    .type __xbrtime_atomic_fetch_and_4, @function
  __xbrtime_atomic_fetch_and_4:
    eaddie e10, a2, 0
    eamoand.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_fetch_and_4, .-__xbrtime_atomic_fetch_and_4

     #---------------------------------------------------

    .global __xbrtime_atomic_fetch_and_8
    .type __xbrtime_atomic_fetch_and_8, @function
  __xbrtime_atomic_fetch_and_8:
    eaddie e10, a2, 0
    eamoand.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_fetch_and_8, .-__xbrtime_atomic_fetch_and_8

    #---------------------------------------------------

    .global __xbrtime_atomic_fetch_or_4
    .type __xbrtime_atomic_fetch_or_4, @function
  __xbrtime_atomic_fetch_or_4:
    eaddie e10, a2, 0
    eamoor.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_fetch_or_4, .-__xbrtime_atomic_fetch_or_4

     #---------------------------------------------------

    .global __xbrtime_atomic_fetch_or_8
    .type __xbrtime_atomic_fetch_or_8, @function
  __xbrtime_atomic_fetch_or_8:
    eaddie e10, a2, 0
    eamoor.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_fetch_or_8, .-__xbrtime_atomic_fetch_or_8

    #---------------------------------------------------

    .global __xbrtime_atomic_fetch_xor_4
    .type __xbrtime_atomic_fetch_xor_4, @function
  __xbrtime_atomic_fetch_xor_4:
    eaddie e10, a2, 0
    eamoxor.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_fetch_xor_4, .-__xbrtime_atomic_fetch_xor_4

     #---------------------------------------------------

    .global __xbrtime_atomic_fetch_xor_8
    .type __xbrtime_atomic_fetch_xor_8, @function
  __xbrtime_atomic_fetch_xor_8:
    eaddie e10, a2, 0
    eamoxor.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_fetch_xor_8, .-__xbrtime_atomic_fetch_xor_8

    #---------------------------------------------------
