#
# _XBRTIME_ATOMICS_ASM_S_
#
# Copyright (C) 2017-2019 Tactical Computing Laboratories, LLC
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
  # Atomic Function Calling Convention
  #   - a0 = base address of memory location
  #   - a1 = op value (expected value for cas)
  #   - a2 = remote pe
  #   - a3 = desired value for cas
  #---------------------------------------------------

    .global __xbrtime_atomic_swap_u4
    .type __xbrtime_atomic_swap_u4, @function
  __xbrtime_atomic_swap_u4:
    eaddie e10, a2, 0
    eamoswap.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_swap_u4, .-__xbrtime_atomic_swap_u4

    #---------------------------------------------------

    .global __xbrtime_atomic_swap_s4
    .type __xbrtime_atomic_swap_s4, @function
  __xbrtime_atomic_swap_s4:
    eaddie e10, a2, 0
    eamoswap.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_swap_s4, .-__xbrtime_atomic_swap_s4

    #---------------------------------------------------

    .global __xbrtime_atomic_swap_u8
    .type __xbrtime_atomic_swap_u8, @function
  __xbrtime_atomic_swap_u8:
    eaddie e10, a2, 0
    eamoswap.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_swap_u8, .-__xbrtime_atomic_swap_u8

    #---------------------------------------------------

    .global __xbrtime_atomic_swap_s8
    .type __xbrtime_atomic_swap_s8, @function
  __xbrtime_atomic_swap_s8:
    eaddie e10, a2, 0
    eamoswap.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_swap_s8, .-__xbrtime_atomic_swap_s8

    #---------------------------------------------------

    .global __xbrtime_atomic_add_u4
    .type __xbrtime_atomic_add_u4, @function
  __xbrtime_atomic_add_u4:
    eaddie e10, a2, 0
    eamoadd.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_add_u4, .-__xbrtime_atomic_add_u4

    #---------------------------------------------------

    .global __xbrtime_atomic_add_s4
    .type __xbrtime_atomic_add_s4, @function
  __xbrtime_atomic_add_s4:
    eaddie e10, a2, 0
    eamoadd.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_add_s4, .-__xbrtime_atomic_add_s4

    #---------------------------------------------------

    .global __xbrtime_atomic_add_u8
    .type __xbrtime_atomic_add_u8, @function
  __xbrtime_atomic_add_u8:
    eaddie e10, a2, 0
    eamoadd.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_add_u8, .-__xbrtime_atomic_add_u8

    #---------------------------------------------------

    .global __xbrtime_atomic_add_s8
    .type __xbrtime_atomic_add_s8, @function
  __xbrtime_atomic_add_s8:
    eaddie e10, a2, 0
    eamoadd.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_add_s8, .-__xbrtime_atomic_add_s8

    #---------------------------------------------------


    .global __xbrtime_atomic_bxor_u4
    .type __xbrtime_atomic_bxor_u4, @function
  __xbrtime_atomic_bxor_u4:
    eaddie e10, a2, 0
    eamoxor.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_bxor_u4, .-__xbrtime_atomic_bxor_u4

    #---------------------------------------------------

    .global __xbrtime_atomic_bxor_s4
    .type __xbrtime_atomic_bxor_s4, @function
  __xbrtime_atomic_bxor_s4:
    eaddie e10, a2, 0
    eamoxor.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_bxor_s4, .-__xbrtime_atomic_bxor_s4

    #---------------------------------------------------

    .global __xbrtime_atomic_bxor_u8
    .type __xbrtime_atomic_bxor_u8, @function
  __xbrtime_atomic_bxor_u8:
    eaddie e10, a2, 0
    eamoxor.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_bxor_u8, .-__xbrtime_atomic_bxor_u8

    #---------------------------------------------------

    .global __xbrtime_atomic_bxor_s8
    .type __xbrtime_atomic_bxor_s8, @function
  __xbrtime_atomic_bxor_s8:
    eaddie e10, a2, 0
    eamoxor.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_bxor_s8, .-__xbrtime_atomic_bxor_s8

    #---------------------------------------------------

    .global __xbrtime_atomic_band_u4
    .type __xbrtime_atomic_band_u4, @function
  __xbrtime_atomic_band_u4:
    eaddie e10, a2, 0
    eamoand.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_band_u4, .-__xbrtime_atomic_band_u4

    #---------------------------------------------------

    .global __xbrtime_atomic_band_s4
    .type __xbrtime_atomic_band_s4, @function
  __xbrtime_atomic_band_s4:
    eaddie e10, a2, 0
    eamoand.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_band_s4, .-__xbrtime_atomic_band_s4

    #---------------------------------------------------

    .global __xbrtime_atomic_band_u8
    .type __xbrtime_atomic_band_u8, @function
  __xbrtime_atomic_band_u8:
    eaddie e10, a2, 0
    eamoand.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_band_u8, .-__xbrtime_atomic_band_u8

    #---------------------------------------------------

    .global __xbrtime_atomic_band_s8
    .type __xbrtime_atomic_band_s8, @function
  __xbrtime_atomic_band_s8:
    eaddie e10, a2, 0
    eamoand.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_band_s8, .-__xbrtime_atomic_band_s8

    #---------------------------------------------------

    .global __xbrtime_atomic_bor_u4
    .type __xbrtime_atomic_bor_u4, @function
  __xbrtime_atomic_bor_u4:
    eaddie e10, a2, 0
    eamoor.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_bor_u4, .-__xbrtime_atomic_bor_u4

    #---------------------------------------------------

    .global __xbrtime_atomic_bor_s4
    .type __xbrtime_atomic_bor_s4, @function
  __xbrtime_atomic_bor_s4:
    eaddie e10, a2, 0
    eamoor.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_bor_s4, .-__xbrtime_atomic_bor_s4

    #---------------------------------------------------

    .global __xbrtime_atomic_bor_u8
    .type __xbrtime_atomic_bor_u8, @function
  __xbrtime_atomic_bor_u8:
    eaddie e10, a2, 0
    eamoor.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_bor_u8, .-__xbrtime_atomic_bor_u8

    #---------------------------------------------------

    .global __xbrtime_atomic_bor_s8
    .type __xbrtime_atomic_bor_s8, @function
  __xbrtime_atomic_bor_s8:
    eaddie e10, a2, 0
    eamoor.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_bor_s8, .-__xbrtime_atomic_bor_s8

    #---------------------------------------------------

    .global __xbrtime_atomic_min_u4
    .type __xbrtime_atomic_min_u4, @function
  __xbrtime_atomic_min_u4:
    eaddie e10, a2, 0
    eamominu.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_min_u4, .-__xbrtime_atomic_min_u4

    #---------------------------------------------------

    .global __xbrtime_atomic_min_s4
    .type __xbrtime_atomic_min_s4, @function
  __xbrtime_atomic_min_s4:
    eaddie e10, a2, 0
    eamomin.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_min_s4, .-__xbrtime_atomic_min_s4

    #---------------------------------------------------

    .global __xbrtime_atomic_min_u8
    .type __xbrtime_atomic_min_u8, @function
  __xbrtime_atomic_min_u8:
    eaddie e10, a2, 0
    eamominu.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_min_u8, .-__xbrtime_atomic_min_u8

    #---------------------------------------------------

    .global __xbrtime_atomic_min_s8
    .type __xbrtime_atomic_min_s8, @function
  __xbrtime_atomic_min_s8:
    eaddie e10, a2, 0
    eamomin.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_min_s8, .-__xbrtime_atomic_min_s8

    #---------------------------------------------------

    .global __xbrtime_atomic_max_u4
    .type __xbrtime_atomic_max_u4, @function
  __xbrtime_atomic_max_u4:
    eaddie e10, a2, 0
    eamomaxu.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_max_u4, .-__xbrtime_atomic_max_u4

    #---------------------------------------------------

    .global __xbrtime_atomic_max_s4
    .type __xbrtime_atomic_max_s4, @function
  __xbrtime_atomic_max_s4:
    eaddie e10, a2, 0
    eamomax.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_max_s4, .-__xbrtime_atomic_max_s4

    #---------------------------------------------------

    .global __xbrtime_atomic_max_u8
    .type __xbrtime_atomic_max_u8, @function
    __xbrtime_atomic_max_u8:
    eaddie e10, a2, 0
    eamomaxu.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_max_u8, .-__xbrtime_atomic_max_u8

    #---------------------------------------------------

    .global __xbrtime_atomic_max_s8
    .type __xbrtime_atomic_max_s8, @function
  __xbrtime_atomic_max_s8:
    eaddie e10, a2, 0
    eamomax.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_max_s8, .-__xbrtime_atomic_max_s8

    #---------------------------------------------------

    .global __xbrtime_atomic_compare_swap_u4
    .type __xbrtime_atomic_compare_swap_u4, @function
  __xbrtime_atomic_compare_swap_u4:
    eaddie e10, a2, 0
  _cas_u4:
    elr.w t0, (a0)             # Load original value
    bne t0, a1, _cas_fail_u4   # Doesn't match, so fail.
    esc.w t0, a3, (a0)         # Try to update.
    bnez t0, _cas_u4           # Retry if store-conditional failed
    li a0, 0                   # Set return to success
    jr ra                      # Return
  _cas_fail_u4:
    li a0, 1                   # Set return to failure.
    jr ra                      # Return
    .size __xbrtime_atomic_compare_swap_u4, .-__xbrtime_atomic_compare_swap_u4

    #---------------------------------------------------

    .global __xbrtime_atomic_compare_swap_s4
    .type __xbrtime_atomic_compare_swap_s4, @function
  __xbrtime_atomic_compare_swap_s4:
    eaddie e10, a2, 0
  _cas_s4:
    elr.w t0, (a0)             # Load original value
    bne t0, a1, _cas_fail_s4   # Doesn't match, so fail.
    esc.w t0, a3, (a0)         # Try to update.
    bnez t0, _cas_s4           # Retry if store-conditional failed
    li a0, 0                   # Set return to success
    jr ra                      # Return
  _cas_fail_s4:
    li a0, 1                   # Set return to failure.
    jr ra                      # Return
    .size __xbrtime_atomic_compare_swap_s4, .-__xbrtime_atomic_compare_swap_s4

    #---------------------------------------------------

    .global __xbrtime_atomic_compare_swap_u8
    .type __xbrtime_atomic_compare_swap_u8, @function
  __xbrtime_atomic_compare_swap_u8:
    eaddie e10, a2, 0
  _cas_u8:
    elr.d t0, (a0)             # Load original value
    bne t0, a1, _cas_fail_u8   # Doesn't match, so fail.
    esc.d t0, a3, (a0)         # Try to update.
    bnez t0, _cas_u8           # Retry if store-conditional failed
    li a0, 0                   # Set return to success
    jr ra                      # Return
  _cas_fail_u8:
    li a0, 1                   # Set return to failure.
    jr ra                      # Return
    .size __xbrtime_atomic_compare_swap_u8, .-__xbrtime_atomic_compare_swap_u8

    #---------------------------------------------------

    .global __xbrtime_atomic_compare_swap_s8
    .type __xbrtime_atomic_compare_swap_s8, @function
  __xbrtime_atomic_compare_swap_s8:
    eaddie e10, a2, 0
  _cas_s8:
    elr.d t0, (a0)             # Load original value
    bne t0, a1, _cas_fail_s8   # Doesn't match, so fail.
    esc.d t0, a3, (a0)         # Try to update.
    bnez t0, _cas_s8           # Retry if store-conditional failed
    li a0, 0                   # Set return to success
    jr ra                      # Return
  _cas_fail_s8:
    li a0, 1                   # Set return to failure.
    jr ra                      # Return
    .size __xbrtime_atomic_compare_swap_s8, .-__xbrtime_atomic_compare_swap_s8

    #---------------------------------------------------
