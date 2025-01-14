#
# _XBRTIME_API_ASM_S_
#
# Copyright (C) 2017-2024 Tactical Computing Laboratories, LLC
# All Rights Reserved
# contact@tactcomplabs.com
#
# This file is a part of the XBGAS-RUNTIME package.  For license
# information, see the LICENSE file in the top level directory
# of the distribution.
#

  .file "xbrtime_api_asm.s"
  .text
  .align 1

  #---------------------------------------------------
  # xBGAS ASM API functions are formatted as follows:
  # __xbrtime_{get,put}_OPERAND_{seq,agg}
  #   where,
  #   - {get,put} correponds to receive and send
  #   - OPERAND is one of:
  #     - u1 = unsigned one byte
  #     - u2 = unsigned two byte
  #     - u4 = unsigned four byte
  #     - u8 = unsigned eight byte
  #     - s1 = signed one byte
  #     - s2 = signed two byte
  #     - s4 = signed four byte
  #     - s8 = signed eight byte
  #   - {seq,agg} corresponds to sequential
  #             and aggregated transfers

  #---------------------------------------------------
  # Put Calling Convention
  #   - a0 = dest address
  #   - a1 = value 
  #   - a2 = remote pe
  #---------------------------------------------------

  .global __xbrtime_put_1
  .type __xbrtime_put_1, @function
__xbrtime_put_1:
  eaddie e10, a2, 0
  esb a1, 0(a0)
  ret
  .size __xbrtime_put_1, .-__xbrtime_put_1

  #---------------------------------------------------

  .global __xbrtime_put_2
  .type __xbrtime_put_2, @function
__xbrtime_put_2:
  eaddie e10, a2, 0
  esh a1, 0(a0)
  ret
  .size __xbrtime_put_2, .-__xbrtime_put_2

  #---------------------------------------------------

  .global __xbrtime_put_4
  .type __xbrtime_put_4, @function
__xbrtime_put_4:
  eaddie e10, a2, 0
  esw a1, 0(a0)
  ret
  .size __xbrtime_put_4, .-__xbrtime_put_4

  #---------------------------------------------------

  .global __xbrtime_put_f4
  .type __xbrtime_put_f4, @function
__xbrtime_put_f4:
  eaddie e10, a2, 0
  fmv.x.w t0, fa0
  esw t0, 0(a0)
  ret
  .size __xbrtime_put_f4, .-__xbrtime_put_f4

  #---------------------------------------------------

  .global __xbrtime_put_8
  .type __xbrtime_put_8, @function
__xbrtime_put_8:
  eaddie e10, a2, 0
  esd a1, 0(a0)
  ret
  .size __xbrtime_put_8, .-__xbrtime_put_8

  #---------------------------------------------------

  .global __xbrtime_put_f8
  .type __xbrtime_put_f8, @function
__xbrtime_put_f8:
  eaddie e10, a2, 0
  fmv.x.d t0, fa0
  esd t0, 0(a0)
  ret
  .size __xbrtime_put_f8, .-__xbrtime_put_f8

  #---------------------------------------------------
  # Get Calling Convention
  #   - a0 = source address
  #   - a1 = remote pe
  #---------------------------------------------------

  .global __xbrtime_get_u1
  .type __xbrtime_get_u1, @function
__xbrtime_get_u1:
  eaddie e10, a1, 0
  elbu a0, 0(a0)
  ret
  .size __xbrtime_get_u1, .-__xbrtime_get_u1

  #---------------------------------------------------

  .global __xbrtime_get_s1
  .type __xbrtime_get_s1, @function
__xbrtime_get_s1:
  eaddie e10, a1, 0
  elb a0, 0(a0)
  ret
  .size __xbrtime_get_s1, .-__xbrtime_get_s1

  #---------------------------------------------------

  .global __xbrtime_get_u2
  .type __xbrtime_get_u2, @function
__xbrtime_get_u2:
  eaddie e10, a1, 0
  elhu a0, 0(a0)
  ret
  .size __xbrtime_get_u2, .-__xbrtime_get_u2

  #---------------------------------------------------

  .global __xbrtime_get_s2
  .type __xbrtime_get_s2, @function
__xbrtime_get_s2:
  eaddie e10, a1, 0
  elh a0, 0(a0)
  ret
  .size __xbrtime_get_s2, .-__xbrtime_get_s2

  #---------------------------------------------------

  .global __xbrtime_get_4
  .type __xbrtime_get_4, @function
__xbrtime_get_4:
  eaddie e10, a1, 0
  elw a0, 0(a0)
  ret
  .size __xbrtime_get_4, .-__xbrtime_get_4

  #---------------------------------------------------

  .global __xbrtime_get_f4
  .type __xbrtime_get_f4, @function
__xbrtime_get_f4:
  eaddie e10, a1, 0
  elw t0, 0(a0)
  fmv.w.x fa0, t0
  ret
  .size __xbrtime_get_f4, .-__xbrtime_get_f4

  #---------------------------------------------------

  .global __xbrtime_get_8
  .type __xbrtime_get_8, @function
__xbrtime_get_8:
  eaddie e10, a1, 0
  eld a0, 0(a0)
  ret
  .size __xbrtime_get_8, .-__xbrtime_get_8

  #---------------------------------------------------

  .global __xbrtime_get_f8
  .type __xbrtime_get_f8, @function
__xbrtime_get_f8:
  eaddie e10, a1, 0
  eld t0, 0(a0)
  fmv.d.x fa0, t0
  ret
  .size __xbrtime_get_f8, .-__xbrtime_get_f8

  #---------------------------------------------------
  # Bulk Put/Get Calling Convention
  #   - a0 = dest address
  #   - a1 = source address
  #   - a2 = nelems
  #   - a3 = remote pe
  #---------------------------------------------------

  .global __xbrtime_put_1_agg
  .type __xbrtime_put_1_agg, @function
__xbrtime_put_1_agg:
  eaddie e10, a3, 0
  ebsb a0, a1, a0, a2
.put_1_agg_wait:
  beq a0, x0, .put_1_agg_wait
  ret
  .size __xbrtime_put_1_agg, .-__xbrtime_put_1_agg

  #---------------------------------------------------

  .global __xbrtime_put_2_agg
  .type __xbrtime_put_2_agg, @function
__xbrtime_put_2_agg:
  eaddie e10, a3, 0
  ebsh a0, a1, a0, a2
.put_2_agg_wait:
  beq a0, x0, .put_2_agg_wait
  ret
  .size __xbrtime_put_2_agg, .-__xbrtime_put_2_agg

  #---------------------------------------------------

  .global __xbrtime_put_4_agg
  .type __xbrtime_put_4_agg, @function
__xbrtime_put_4_agg:
  eaddie e10, a3, 0
  ebsw a0, a1, a0, a2
.put_4_agg_wait:
  beq a0, x0, .put_4_agg_wait
  ret
  .size __xbrtime_put_4_agg, .-__xbrtime_put_4_agg

  #---------------------------------------------------

  .global __xbrtime_put_8_agg
  .type __xbrtime_put_8_agg, @function
__xbrtime_put_8_agg:
  eaddie e10, a3, 0
  ebsd a0, a1, a0, a2
.put_8_agg_wait:
  beq a0, x0, .put_8_agg_wait
  ret
  .size __xbrtime_put_8_agg, .-__xbrtime_put_8_agg

  #---------------------------------------------------

  .global __xbrtime_put_1_agg_nbi
  .type __xbrtime_put_1_agg_nbi, @function
__xbrtime_put_1_agg_nbi:
  eaddie e10, a3, 0
  ebsb x0, a1, a0, a2
  ret
  .size __xbrtime_put_1_agg_nbi, .-__xbrtime_put_1_agg_nbi

  #---------------------------------------------------

  .global __xbrtime_put_2_agg_nbi
  .type __xbrtime_put_2_agg_nbi, @function
__xbrtime_put_2_agg_nbi:
  eaddie e10, a3, 0
  ebsh x0, a1, a0, a2
  ret
  .size __xbrtime_put_2_agg_nbi, .-__xbrtime_put_2_agg_nbi

  #---------------------------------------------------

  .global __xbrtime_put_4_agg_nbi
  .type __xbrtime_put_4_agg_nbi, @function
__xbrtime_put_4_agg_nbi:
  eaddie e10, a3, 0
  ebsw x0, a1, a0, a2
  ret
  .size __xbrtime_put_4_agg_nbi, .-__xbrtime_put_4_agg_nbi

  #---------------------------------------------------

  .global __xbrtime_put_8_agg_nbi
  .type __xbrtime_put_8_agg_nbi, @function
__xbrtime_put_8_agg_nbi:
  eaddie e10, a3, 0
  ebsd x0, a1, a0, a2
  ret
  .size __xbrtime_put_8_agg_nbi, .-__xbrtime_put_8_agg_nbi

  #---------------------------------------------------

  .global __xbrtime_get_1_agg
  .type __xbrtime_get_1_agg, @function
__xbrtime_get_1_agg:
  eaddie e11, a3, 0
  eblb a0, a0, a1, a2
.get_1_agg_wait:
  beq a0, x0, .get_1_agg_wait
  ret
  .size __xbrtime_get_1_agg, .-__xbrtime_get_1_agg

  #---------------------------------------------------

  .global __xbrtime_get_2_agg
  .type __xbrtime_get_2_agg, @function
__xbrtime_get_2_agg:
  eaddie e11, a3, 0
  eblh a0, a0, a1, a2
.get_2_agg_wait:
  beq a0, x0, .get_2_agg_wait
  ret
  .size __xbrtime_get_2_agg, .-__xbrtime_get_2_agg

  #---------------------------------------------------

  .global __xbrtime_get_4_agg
  .type __xbrtime_get_4_agg, @function
__xbrtime_get_4_agg:
  eaddie e11, a3, 0
  eblw a0, a0, a1, a2
.get_4_agg_wait:
  beq a0, x0, .get_4_agg_wait
  ret
  .size __xbrtime_get_4_agg, .-__xbrtime_get_4_agg

  #---------------------------------------------------

  .global __xbrtime_get_8_agg
  .type __xbrtime_get_8_agg, @function
__xbrtime_get_8_agg:
  eaddie e11, a3, 0
  ebld a0, a0, a1, a2
.get_8_agg_wait:
  beq a0, x0, .get_8_agg_wait
  ret
  .size __xbrtime_get_8_agg, .-__xbrtime_get_8_agg

  #---------------------------------------------------

  .global __xbrtime_get_1_agg_nbi
  .type __xbrtime_get_1_agg_nbi, @function
__xbrtime_get_1_agg_nbi:
  eaddie e11, a3, 0
  eblb x0, a0, a1, a2
  ret
  .size __xbrtime_get_1_agg_nbi, .-__xbrtime_get_1_agg_nbi

  #---------------------------------------------------

  .global __xbrtime_get_2_agg_nbi
  .type __xbrtime_get_2_agg_nbi, @function
__xbrtime_get_2_agg_nbi:
  eaddie e11, a3, 0
  eblh x0, a0, a1, a2
  ret
  .size __xbrtime_get_2_agg_nbi, .-__xbrtime_get_2_agg_nbi

  #---------------------------------------------------

  .global __xbrtime_get_4_agg_nbi
  .type __xbrtime_get_4_agg_nbi, @function
__xbrtime_get_4_agg_nbi:
  eaddie e11, a3, 0
  eblw x0, a0, a1, a2
  ret
  .size __xbrtime_get_4_agg_nbi, .-__xbrtime_get_4_agg_nbi

  #---------------------------------------------------

  .global __xbrtime_get_8_agg_nbi
  .type __xbrtime_get_8_agg_nbi, @function
__xbrtime_get_8_agg_nbi:
  eaddie e11, a3, 0
  ebld x0, a0, a1, a2
  ret
  .size __xbrtime_get_8_agg_nbi, .-__xbrtime_get_8_agg_nbi

  #---------------------------------------------------
  # Sequential Put/Get Calling Convention
  #   - a0 = dest address
  #   - a1 = source address
  #   - a2 = stride of dest 
  #   - a3 = stride of source 
  #   - a4 = nelems
  #   - a5 = remote pe
  #---------------------------------------------------

  .global __xbrtime_put_u1_seq
  .type __xbrtime_put_u1_seq, @function
__xbrtime_put_u1_seq:
  eaddie e10, a5, 0
  mv x31, zero
.put_u1_seq:
  lbu x30, 0(a1)
  add a1, a1, a3
  add x31, x31, 1
  esb x30, 0(a0)
  add a0, a0, a2
  bne x31, a4, .put_u1_seq
  ret
  .size __xbrtime_put_u1_seq, .-__xbrtime_put_u1_seq

  #---------------------------------------------------

  .global __xbrtime_put_s1_seq
  .type __xbrtime_put_s1_seq, @function
__xbrtime_put_s1_seq:
  eaddie e10, a5, 0
  mv x31, zero
.put_s1_seq:
  lb x30, 0(a1)
  add a1, a1, a3
  add x31, x31, 1
  esb x30, 0(a0)
  add a0, a0, a2
  bne x31, a4, .put_s1_seq
  ret
  .size __xbrtime_put_s1_seq, .-__xbrtime_put_s1_seq

  #---------------------------------------------------

  .global __xbrtime_put_u2_seq
  .type __xbrtime_put_u2_seq, @function
__xbrtime_put_u2_seq:
  eaddie e10, a5, 0
  mv x31, zero
.put_u2_seq:
  lhu x30, 0(a1)
  add a1, a1, a3
  add x31, x31, 1
  esh x30, 0(a0)
  add a0, a0, a2
  bne x31, a4, .put_u2_seq
  ret
  .size __xbrtime_put_u2_seq, .-__xbrtime_put_u2_seq

  #---------------------------------------------------

  .global __xbrtime_put_s2_seq
  .type __xbrtime_put_s2_seq, @function
__xbrtime_put_s2_seq:
  eaddie e10, a5, 0
  mv x31, zero
.put_s2_seq:
  lh x30, 0(a1)
  add a1, a1, a3
  add x31, x31, 1
  esh x30, 0(a0)
  add a0, a0, a2
  bne x31, a4, .put_s2_seq
  ret
  .size __xbrtime_put_s2_seq, .-__xbrtime_put_s2_seq

  #---------------------------------------------------

  .global __xbrtime_put_4_seq
  .type __xbrtime_put_4_seq, @function
__xbrtime_put_4_seq:
  eaddie e10, a5, 0
  mv x31, zero
.put_4_seq:
  lw x30, 0(a1)
  add a1, a1, a3
  add x31, x31, 1
  esw x30, 0(a0)
  add a0, a0, a2
  bne x31, a4, .put_4_seq
  ret
  .size __xbrtime_put_4_seq, .-__xbrtime_put_4_seq

  #---------------------------------------------------

  .global __xbrtime_put_8_seq
  .type __xbrtime_put_8_seq, @function
__xbrtime_put_8_seq:
  eaddie e10, a5, 0
  mv x31, zero
.put_8_seq:
  ld x30, 0(a1)
  add a1, a1, a3
  add x31, x31, 1
  esd x30, 0(a0)
  add a0, a0, a2
  bne x31, a4, .put_8_seq
  ret
  .size __xbrtime_put_8_seq, .-__xbrtime_put_8_seq

  #---------------------------------------------------

  .global __xbrtime_get_u1_seq
  .type __xbrtime_get_u1_seq, @function
__xbrtime_get_u1_seq:
  eaddie e11, a5, 0
  mv x31, zero
.get_u1_seq:
  elbu x30, 0(a1)
  add a1, a1, a3
  add x31, x31, 1
  sb x30, 0(a0)
  add a0, a0, a2
  bne x31,a4,.get_u1_seq
  ret
  .size __xbrtime_get_u1_seq, .-__xbrtime_get_u1_seq

  #---------------------------------------------------

  .global __xbrtime_get_s1_seq
  .type __xbrtime_get_s1_seq, @function
__xbrtime_get_s1_seq:
  eaddie e11, a5, 0
  mv x31, zero
.get_s1_seq:
  elb x30, 0(a1)
  add a1, a1, a3
  add x31, x31, 1
  sb x30, 0(a0)
  add a0, a0, a2
  bne x31,a4,.get_s1_seq
  ret
  .size __xbrtime_get_s1_seq, .-__xbrtime_get_s1_seq

  #---------------------------------------------------

  .global __xbrtime_get_u2_seq
  .type __xbrtime_get_u2_seq, @function
__xbrtime_get_u2_seq:
  eaddie e11, a5, 0
  mv x31, zero
.get_u2_seq:
  elhu x30, 0(a1)
  add a1, a1, a3
  add x31, x31, 1
  sb x30, 0(a0)
  add a0, a0, a2
  bne x31,a4,.get_u2_seq
  ret
  .size __xbrtime_get_u2_seq, .-__xbrtime_get_u2_seq

  #---------------------------------------------------

  .global __xbrtime_get_s2_seq
  .type __xbrtime_get_s2_seq, @function
__xbrtime_get_s2_seq:
  eaddie e11, a5, 0
  mv x31, zero
.get_s2_seq:
  elh x30, 0(a1)
  add a1, a1, a3
  add x31, x31, 1
  sh x30, 0(a0)
  add a0, a0, a2
  bne x31,a4,.get_s2_seq
  ret
  .size __xbrtime_get_s2_seq, .-__xbrtime_get_s2_seq

  #---------------------------------------------------

  .global __xbrtime_get_4_seq
  .type __xbrtime_get_4_seq, @function
__xbrtime_get_4_seq:
  eaddie e11, a5, 0
  mv x31, zero
.get_4_seq:
  elw x30, 0(a1)
  add a1, a1, a3
  add x31, x31, 1
  sw x30, 0(a0)
  add a0, a0, a2
  bne x31,a4,.get_4_seq
  ret
  .size __xbrtime_get_4_seq, .-__xbrtime_get_4_seq

  #---------------------------------------------------

    .global __xbrtime_get_8_seq
  .type __xbrtime_get_8_seq, @function
__xbrtime_get_8_seq:
  eaddie e11, a5, 0
  mv x31, zero
.get_8_seq:
  eld x30, 0(a1)
  add a1, a1, a3
  add x31, x31, 1
  sd x30, 0(a0)
  add a0, a0, a2
  bne x31,a4,.get_8_seq
  ret
  .size __xbrtime_get_8_seq, .-__xbrtime_get_8_seq

  #---------------------------------------------------

  #-- EOF
