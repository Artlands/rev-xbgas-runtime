#
# _XBRTIME_ATOMICS_ASM_S_
#
# Copyright (C) 2017-2024 Tactical Computing Laoratories, LLC
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
  #     - and = bitwise AND
  #     - or = bitwise OR
  #     - xor = bitwise XOR
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

    .global __xbrtime_atomic_add_s4
    .type __xbrtime_atomic_add_s4, @function
  __xbrtime_atomic_add_s4:
    eaddie e10, a2, 0
    eamoadd.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_add_s4, .-__xbrtime_atomic_add_s4

    #---------------------------------------------------

    .global __xbrtime_atomic_add_s8
    .type __xbrtime_atomic_add_s8, @function
  __xbrtime_atomic_add_s8:
    eaddie e10, a2, 0
    eamoadd.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_add_s8, .-__xbrtime_atomic_add_s8

    #---------------------------------------------------

    .global __xbrtime_atomic_add_u4
    .type __xbrtime_atomic_add_u4, @function
  __xbrtime_atomic_add_u4:
    eaddie e10, a2, 0
    eamoadd.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_add_u4, .-__xbrtime_atomic_add_u4

    #---------------------------------------------------

    .global __xbrtime_atomic_add_u8
    .type __xbrtime_atomic_add_u8, @function
  __xbrtime_atomic_add_u8:
    eaddie e10, a2, 0
    eamoadd.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_add_u8, .-__xbrtime_atomic_add_u8

    #---------------------------------------------------

    .global __xbrtime_atomic_and_s4
    .type __xbrtime_atomic_and_s4, @function
  __xbrtime_atomic_and_s4:
    eaddie e10, a2, 0
    eamoand.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_and_s4, .-__xbrtime_atomic_and_s4

    #---------------------------------------------------

    .global __xbrtime_atomic_and_s8
    .type __xbrtime_atomic_and_s8, @function
  __xbrtime_atomic_and_s8:
    eaddie e10, a2, 0
    eamoand.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_and_s8, .-__xbrtime_atomic_and_s8

    #---------------------------------------------------

    .global __xbrtime_atomic_and_u4
    .type __xbrtime_atomic_and_u4, @function
  __xbrtime_atomic_and_u4:
    eaddie e10, a2, 0
    eamoand.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_and_u4, .-__xbrtime_atomic_and_u4

    #---------------------------------------------------

    .global __xbrtime_atomic_and_u8
    .type __xbrtime_atomic_and_u8, @function
  __xbrtime_atomic_and_u8:
    eaddie e10, a2, 0
    eamoand.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_and_u8, .-__xbrtime_atomic_and_u8

    #---------------------------------------------------

    .global __xbrtime_atomic_or_s4
    .type __xbrtime_atomic_or_s4, @function
  __xbrtime_atomic_or_s4:
    eaddie e10, a2, 0
    eamoor.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_or_s4, .-__xbrtime_atomic_or_s4

    #---------------------------------------------------

    .global __xbrtime_atomic_or_s8
    .type __xbrtime_atomic_or_s8, @function
  __xbrtime_atomic_or_s8:
    eaddie e10, a2, 0
    eamoor.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_or_s8, .-__xbrtime_atomic_or_s8

    #---------------------------------------------------

    .global __xbrtime_atomic_or_u4
    .type __xbrtime_atomic_or_u4, @function
  __xbrtime_atomic_or_u4:
    eaddie e10, a2, 0
    eamoor.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_or_u4, .-__xbrtime_atomic_or_u4

    #---------------------------------------------------

    .global __xbrtime_atomic_or_u8
    .type __xbrtime_atomic_or_u8, @function
  __xbrtime_atomic_or_u8:
    eaddie e10, a2, 0
    eamoor.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_or_u8, .-__xbrtime_atomic_or_u8

    #---------------------------------------------------

    .global __xbrtime_atomic_xor_s4
    .type __xbrtime_atomic_xor_s4, @function
  __xbrtime_atomic_xor_s4:
    eaddie e10, a2, 0
    eamoxor.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_xor_s4, .-__xbrtime_atomic_xor_s4

    #---------------------------------------------------

    .global __xbrtime_atomic_xor_s8
    .type __xbrtime_atomic_xor_s8, @function
  __xbrtime_atomic_xor_s8:
    eaddie e10, a2, 0
    eamoxor.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_xor_s8, .-__xbrtime_atomic_xor_s8

    #---------------------------------------------------

    .global __xbrtime_atomic_xor_u4
    .type __xbrtime_atomic_xor_u4, @function
  __xbrtime_atomic_xor_u4:
    eaddie e10, a2, 0
    eamoxor.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_xor_u4, .-__xbrtime_atomic_xor_u4

    #---------------------------------------------------

    .global __xbrtime_atomic_xor_u8
    .type __xbrtime_atomic_xor_u8, @function
  __xbrtime_atomic_xor_u8:
    eaddie e10, a2, 0
    eamoxor.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_xor_u8, .-__xbrtime_atomic_xor_u8

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

    .global __xbrtime_atomic_set_s4
    .type __xbrtime_atomic_set_s4, @function
  __xbrtime_atomic_set_s4:
    eaddie e10, a2, 0
    eamoswap.w x0, a1, (a0)
    ret
    .size __xbrtime_atomic_set_s4, .-__xbrtime_atomic_set_s4

     #---------------------------------------------------

    .global __xbrtime_atomic_set_s8
    .type __xbrtime_atomic_set_s8, @function
  __xbrtime_atomic_set_s8:
    eaddie e10, a2, 0
    eamoswap.d x0, a1, (a0)
    ret
    .size __xbrtime_atomic_set_s8, .-__xbrtime_atomic_set_s8

    #---------------------------------------------------

    .global __xbrtime_atomic_set_u4
    .type __xbrtime_atomic_set_u4, @function
  __xbrtime_atomic_set_u4:
    eaddie e10, a2, 0
    eamoswap.w x0, a1, (a0)
    ret
    .size __xbrtime_atomic_set_u4, .-__xbrtime_atomic_set_u4

     #---------------------------------------------------

    .global __xbrtime_atomic_set_u8
    .type __xbrtime_atomic_set_u8, @function
  __xbrtime_atomic_set_u8:
    eaddie e10, a2, 0
    eamoswap.d x0, a1, (a0)
    ret
    .size __xbrtime_atomic_set_u8, .-__xbrtime_atomic_set_u8

    #---------------------------------------------------

    .global __xbrtime_atomic_compare_swap_s4
    .type __xbrtime_atomic_compare_swap_s4, @function
  __xbrtime_atomic_compare_swap_s4:
    eaddie e10, a3, 0
    elr.w t0, (a0)             # Load original value
    bne t0, a1, _cas_fail_s4   # Doesn't match, so fail
    esc.w x0, a2, (a0)         # Update
    mv a0, t0                  # Move the returned value to the return register
    ret
  _cas_fail_s4:
    mv a0, t0                  # Move the returned value to the return register
    ret                        # Return
    .size __xbrtime_atomic_compare_swap_s4, .-__xbrtime_atomic_compare_swap_s4

    #---------------------------------------------------

    .global __xbrtime_atomic_compare_swap_s8
    .type __xbrtime_atomic_compare_swap_s8, @function
  __xbrtime_atomic_compare_swap_s8:
    eaddie e10, a3, 0
    elr.d t0, (a0)             # Load original value
    bne t0, a1, _cas_fail_s8   # Doesn't match, so fail
    esc.d x0, a2, (a0)         # Update
    mv a0, t0                  # Move the returned value to the return register
    ret
  _cas_fail_s8:
    mv a0, t0                  # Move the returned value to the return register
    ret                        # Return
    .size __xbrtime_atomic_compare_swap_s8, .-__xbrtime_atomic_compare_swap_s8

    #---------------------------------------------------

    .global __xbrtime_atomic_compare_swap_u4
    .type __xbrtime_atomic_compare_swap_u4, @function
  __xbrtime_atomic_compare_swap_u4:
    eaddie e10, a3, 0
    elr.w t0, (a0)             # Load original value
    bne t0, a1, _cas_fail_u4   # Doesn't match, so fail
    esc.w x0, a2, (a0)         # Update
    mv a0, t0                  # Move the returned value to the return register
    ret
  _cas_fail_u4:
    mv a0, t0                  # Move the returned value to the return register
    ret                        # Return
    .size __xbrtime_atomic_compare_swap_u4, .-__xbrtime_atomic_compare_swap_u4

    #---------------------------------------------------

    .global __xbrtime_atomic_compare_swap_u8
    .type __xbrtime_atomic_compare_swap_u8, @function
  __xbrtime_atomic_compare_swap_u8:
    eaddie e10, a3, 0
    elr.d t0, (a0)             # Load original value
    bne t0, a1, _cas_fail_u8   # Doesn't match, so fail
    esc.d x0, a2, (a0)         # Update
    mv a0, t0                  # Move the returned value to the return register
    ret
  _cas_fail_u8:
    mv a0, t0                  # Move the returned value to the return register
    ret                        # Return
    .size __xbrtime_atomic_compare_swap_u8, .-__xbrtime_atomic_compare_swap_u8

    #---------------------------------------------------

    .global __xbrtime_atomic_swap_s4
    .type __xbrtime_atomic_swap_s4, @function
  __xbrtime_atomic_swap_s4:
    eaddie e10, a2, 0
    eamoswap.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_swap_s4, .-__xbrtime_atomic_swap_s4

     #---------------------------------------------------

    .global __xbrtime_atomic_swap_s8
    .type __xbrtime_atomic_swap_s8, @function
  __xbrtime_atomic_swap_s8:
    eaddie e10, a2, 0
    eamoswap.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_swap_s8, .-__xbrtime_atomic_swap_s8

    #---------------------------------------------------

    .global __xbrtime_atomic_swap_u4
    .type __xbrtime_atomic_swap_u4, @function
  __xbrtime_atomic_swap_u4:
    eaddie e10, a2, 0
    eamoswap.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_swap_u4, .-__xbrtime_atomic_swap_u4

     #---------------------------------------------------

    .global __xbrtime_atomic_swap_u8
    .type __xbrtime_atomic_swap_u8, @function
  __xbrtime_atomic_swap_u8:
    eaddie e10, a2, 0
    eamoswap.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_swap_u8, .-__xbrtime_atomic_swap_u8

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

    .global __xbrtime_atomic_fetch_add_s4
    .type __xbrtime_atomic_fetch_add_s4, @function
  __xbrtime_atomic_fetch_add_s4:
    eaddie e10, a2, 0
    eamoadd.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_fetch_add_s4, .-__xbrtime_atomic_fetch_add_s4

     #---------------------------------------------------

    .global __xbrtime_atomic_fetch_add_s8
    .type __xbrtime_atomic_fetch_add_s8, @function
  __xbrtime_atomic_fetch_add_s8:
    eaddie e10, a2, 0
    eamoadd.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_fetch_add_s8, .-__xbrtime_atomic_fetch_add_s8

    #---------------------------------------------------

    .global __xbrtime_atomic_fetch_add_u4
    .type __xbrtime_atomic_fetch_add_u4, @function
  __xbrtime_atomic_fetch_add_u4:
    eaddie e10, a2, 0
    eamoadd.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_fetch_add_u4, .-__xbrtime_atomic_fetch_add_u4

     #---------------------------------------------------

    .global __xbrtime_atomic_fetch_add_u8
    .type __xbrtime_atomic_fetch_add_u8, @function
  __xbrtime_atomic_fetch_add_u8:
    eaddie e10, a2, 0
    eamoadd.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_fetch_add_u8, .-__xbrtime_atomic_fetch_add_u8

    #---------------------------------------------------

    .global __xbrtime_atomic_fetch_and_s4
    .type __xbrtime_atomic_fetch_and_s4, @function
  __xbrtime_atomic_fetch_and_s4:
    eaddie e10, a2, 0
    eamoand.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_fetch_and_s4, .-__xbrtime_atomic_fetch_and_s4

     #---------------------------------------------------

    .global __xbrtime_atomic_fetch_and_s8
    .type __xbrtime_atomic_fetch_and_s8, @function
  __xbrtime_atomic_fetch_and_s8:
    eaddie e10, a2, 0
    eamoand.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_fetch_and_s8, .-__xbrtime_atomic_fetch_and_s8

    #---------------------------------------------------

    .global __xbrtime_atomic_fetch_and_u4
    .type __xbrtime_atomic_fetch_and_u4, @function
  __xbrtime_atomic_fetch_and_u4:
    eaddie e10, a2, 0
    eamoand.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_fetch_and_u4, .-__xbrtime_atomic_fetch_and_u4

     #---------------------------------------------------

    .global __xbrtime_atomic_fetch_and_u8
    .type __xbrtime_atomic_fetch_and_u8, @function
  __xbrtime_atomic_fetch_and_u8:
    eaddie e10, a2, 0
    eamoand.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_fetch_and_u8, .-__xbrtime_atomic_fetch_and_u8

    #---------------------------------------------------

    .global __xbrtime_atomic_fetch_or_s4
    .type __xbrtime_atomic_fetch_or_s4, @function
  __xbrtime_atomic_fetch_or_s4:
    eaddie e10, a2, 0
    eamoor.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_fetch_or_s4, .-__xbrtime_atomic_fetch_or_s4

     #---------------------------------------------------

    .global __xbrtime_atomic_fetch_or_s8
    .type __xbrtime_atomic_fetch_or_s8, @function
  __xbrtime_atomic_fetch_or_s8:
    eaddie e10, a2, 0
    eamoor.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_fetch_or_s8, .-__xbrtime_atomic_fetch_or_s8

    #---------------------------------------------------

    .global __xbrtime_atomic_fetch_or_u4
    .type __xbrtime_atomic_fetch_or_u4, @function
  __xbrtime_atomic_fetch_or_u4:
    eaddie e10, a2, 0
    eamoor.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_fetch_or_u4, .-__xbrtime_atomic_fetch_or_u4

     #---------------------------------------------------

    .global __xbrtime_atomic_fetch_or_u8
    .type __xbrtime_atomic_fetch_or_u8, @function
  __xbrtime_atomic_fetch_or_u8:
    eaddie e10, a2, 0
    eamoor.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_fetch_or_u8, .-__xbrtime_atomic_fetch_or_u8

    #---------------------------------------------------

    .global __xbrtime_atomic_fetch_xor_s4
    .type __xbrtime_atomic_fetch_xor_s4, @function
  __xbrtime_atomic_fetch_xor_s4:
    eaddie e10, a2, 0
    eamoxor.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_fetch_xor_s4, .-__xbrtime_atomic_fetch_xor_s4

     #---------------------------------------------------

    .global __xbrtime_atomic_fetch_xor_s8
    .type __xbrtime_atomic_fetch_xor_s8, @function
  __xbrtime_atomic_fetch_xor_s8:
    eaddie e10, a2, 0
    eamoxor.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_fetch_xor_s8, .-__xbrtime_atomic_fetch_xor_s8

    #---------------------------------------------------

    .global __xbrtime_atomic_fetch_xor_u4
    .type __xbrtime_atomic_fetch_xor_u4, @function
  __xbrtime_atomic_fetch_xor_u4:
    eaddie e10, a2, 0
    eamoxor.w a0, a1, (a0)
    ret
    .size __xbrtime_atomic_fetch_xor_u4, .-__xbrtime_atomic_fetch_xor_u4

     #---------------------------------------------------

    .global __xbrtime_atomic_fetch_xor_u8
    .type __xbrtime_atomic_fetch_xor_u8, @function
  __xbrtime_atomic_fetch_xor_u8:
    eaddie e10, a2, 0
    eamoxor.d a0, a1, (a0)
    ret
    .size __xbrtime_atomic_fetch_xor_u8, .-__xbrtime_atomic_fetch_xor_u8

    #---------------------------------------------------
