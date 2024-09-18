/*
 * _XBRTIME_ATOMICS_C_
 *
 * Copyright (C) 2017-2019 Tactical Computing Laboratories, LLC
 * All Rights Reserved
 * contact@tactcomplabs.com
 *
 * This file is a part of the XBGAS-RUNTIME package.  For license
 * information, see the LICENSE file in the top level directory
 * of the distribution.
 *
 */

#include "xbrtime.h"

/* ------------------------------------------------- FUNCTION PROTOTYPES */

uint32_t __xbrtime_atomic_swap_u4(uint64_t base_dest, uint32_t op_val, uint32_t pe);
int32_t __xbrtime_atomic_swap_s4(uint64_t base_dest, int32_t op_val, uint32_t pe);
uint64_t __xbrtime_atomic_swap_u8(uint64_t base_dest, uint64_t op_val, uint32_t pe);
int64_t __xbrtime_atomic_swap_s8(uint64_t base_dest, int64_t op_val, uint32_t pe);

uint32_t __xbrtime_atomic_add_u4(uint64_t base_dest, uint32_t op_val, uint32_t pe);
int32_t __xbrtime_atomic_add_s4(uint64_t base_dest, int32_t op_val, uint32_t pe);
uint64_t __xbrtime_atomic_add_u8(uint64_t base_dest, uint64_t op_val, uint32_t pe);
int64_t __xbrtime_atomic_add_s8(uint64_t base_dest, int64_t op_val, uint32_t pe);

uint32_t __xbrtime_atomic_bxor_u4(uint64_t base_dest, uint32_t op_val, uint32_t pe);
int32_t __xbrtime_atomic_bxor_s4(uint64_t base_dest, int32_t op_val, uint32_t pe);
uint64_t __xbrtime_atomic_bxor_u8(uint64_t base_dest, uint64_t op_val, uint32_t pe);
int64_t __xbrtime_atomic_bxor_s8(uint64_t base_dest, int64_t op_val, uint32_t pe);

uint32_t __xbrtime_atomic_band_u4(uint64_t base_dest, uint32_t op_val, uint32_t pe);
int32_t __xbrtime_atomic_band_s4(uint64_t base_dest, int32_t op_val, uint32_t pe);
uint64_t __xbrtime_atomic_band_u8(uint64_t base_dest, uint64_t op_val, uint32_t pe);
int64_t __xbrtime_atomic_band_s8(uint64_t base_dest, int64_t op_val, uint32_t pe);

uint32_t __xbrtime_atomic_bor_u4(uint64_t base_dest, uint32_t op_val, uint32_t pe);
int32_t __xbrtime_atomic_bor_s4(uint64_t base_dest, int32_t op_val, uint32_t pe);
uint64_t __xbrtime_atomic_bor_u8(uint64_t base_dest, uint64_t op_val, uint32_t pe);
int64_t __xbrtime_atomic_bor_s8(uint64_t base_dest, int64_t op_val, uint32_t pe);

uint32_t __xbrtime_atomic_min_u4(uint64_t base_dest, uint32_t op_val, uint32_t pe);
int32_t __xbrtime_atomic_min_s4(uint64_t base_dest, int32_t op_val, uint32_t pe);
uint64_t __xbrtime_atomic_min_u8(uint64_t base_dest, uint64_t op_val, uint32_t pe);
int64_t __xbrtime_atomic_min_s8(uint64_t base_dest, int64_t op_val, uint32_t pe);

uint32_t __xbrtime_atomic_max_u4(uint64_t base_dest, uint32_t op_val, uint32_t pe);
int32_t __xbrtime_atomic_max_s4(uint64_t base_dest, int32_t op_val, uint32_t pe);
uint64_t __xbrtime_atomic_max_u8(uint64_t base_dest, uint64_t op_val, uint32_t pe);
int64_t __xbrtime_atomic_max_s8(uint64_t base_dest, int64_t op_val, uint32_t pe);

uint32_t __xbrtime_atomic_compare_swap_u4(uint64_t base_dest, uint32_t expected_val, uint32_t pe, uint32_t desired_val);
int32_t __xbrtime_atomic_compare_swap_s4(uint64_t base_dest, int32_t expected_val, uint32_t pe, uint32_t desired_val);
uint64_t __xbrtime_atomic_compare_swap_u8(uint64_t base_dest, uint64_t expected_val, uint32_t pe, uint64_t desired_val);
int64_t __xbrtime_atomic_compare_swap_s8(uint64_t base_dest, int64_t expected_val, uint32_t pe, uint64_t desired_val);

uint32_t xbrtime_decode_pe(int pe);
uint64_t __xbrtime_ltor(uint64_t remote,int pe);

#define XBGAS_ATOMIC_OP(_type, _typename, _typesize, _typecast, _op)                                                        \
_type xbrtime_##_typename##_atomic_##_op(_type *dest, _type op_val, int pe)                                                 \
{                                                                                                                           \
    return ((_type) __xbrtime_atomic_##_op##_##_typesize(__xbrtime_ltor(((uint64_t)dest), pe),                              \
                                                        (_typecast) op_val,                                                 \
                                                        xbrtime_decode_pe(pe)));                                            \
}

#define XBGAS_ATOMIC_CAS(_type, _typename, _typesize, _typecast)                                                            \
_type xbrtime_##_typename##_atomic_compare_swap(_type *dest, _type expected_val, int pe, _type desired_val)                 \
{                                                                                                                           \
    return ((_type) __xbrtime_atomic_compare_swap_##_typesize(__xbrtime_ltor(((uint64_t)dest), pe),                         \
                                                             (_typecast) expected_val,                                      \
                                                             xbrtime_decode_pe(pe),                                         \
                                                             (_typecast) desired_val));                                     \
}

    /* Atomic add */
    XBGAS_ATOMIC_OP(unsigned int, uint, u4, uint32_t, add)
    XBGAS_ATOMIC_OP(unsigned long, ulong, u4, uint32_t, add)
    XBGAS_ATOMIC_OP(uint32_t, uint32, u4, uint32_t, add)
    XBGAS_ATOMIC_OP(int, int, s4, int32_t, add)
    XBGAS_ATOMIC_OP(long, long, s4, int32_t, add)
    XBGAS_ATOMIC_OP(int32_t, int32, s4, int32_t, add)
    XBGAS_ATOMIC_OP(unsigned long long, ulonglong, u8, uint64_t, add)
    XBGAS_ATOMIC_OP(uint64_t, uint64, u8, uint64_t, add)
    XBGAS_ATOMIC_OP(long long, longlong, s8, int64_t, add)
    XBGAS_ATOMIC_OP(int64_t, int64, s8, int64_t, add)

    /* Atomic logical and */
    XBGAS_ATOMIC_OP(unsigned int, uint, u4, uint32_t, band)
    XBGAS_ATOMIC_OP(unsigned long, ulong, u4, uint32_t, band)
    XBGAS_ATOMIC_OP(uint32_t, uint32, u4, uint32_t, band)
    XBGAS_ATOMIC_OP(int, int, s4, int32_t, band)
    XBGAS_ATOMIC_OP(long, long, s4, int32_t, band)
    XBGAS_ATOMIC_OP(int32_t, int32, s4, int32_t, band)
    XBGAS_ATOMIC_OP(unsigned long long, ulonglong, u8, uint64_t, band)
    XBGAS_ATOMIC_OP(uint64_t, uint64, u8, uint64_t, band)
    XBGAS_ATOMIC_OP(long long, longlong, s8, int64_t, band)
    XBGAS_ATOMIC_OP(int64_t, int64, s8, int64_t, band)

    /* Atomic logical or */
    XBGAS_ATOMIC_OP(unsigned int, uint, u4, uint32_t, bor)
    XBGAS_ATOMIC_OP(unsigned long, ulong, u4, uint32_t, bor)
    XBGAS_ATOMIC_OP(uint32_t, uint32, u4, uint32_t, bor)
    XBGAS_ATOMIC_OP(int, int, s4, int32_t, bor)
    XBGAS_ATOMIC_OP(long, long, s4, int32_t, bor)
    XBGAS_ATOMIC_OP(int32_t, int32, s4, int32_t, bor)
    XBGAS_ATOMIC_OP(unsigned long long, ulonglong, u8, uint64_t, bor)
    XBGAS_ATOMIC_OP(uint64_t, uint64, u8, uint64_t, bor)
    XBGAS_ATOMIC_OP(long long, longlong, s8, int64_t, bor)
    XBGAS_ATOMIC_OP(int64_t, int64, s8, int64_t, bor)

    /* Atomic logical exclusive or */
    XBGAS_ATOMIC_OP(unsigned int, uint, u4, uint32_t, bxor)
    XBGAS_ATOMIC_OP(unsigned long, ulong, u4, uint32_t, bxor)
    XBGAS_ATOMIC_OP(uint32_t, uint32, u4, uint32_t, bxor)
    XBGAS_ATOMIC_OP(int, int, s4, int32_t, bxor)
    XBGAS_ATOMIC_OP(long, long, s4, int32_t, bxor)
    XBGAS_ATOMIC_OP(int32_t, int32, s4, int32_t, bxor)
    XBGAS_ATOMIC_OP(unsigned long long, ulonglong, u8, uint64_t, bxor)
    XBGAS_ATOMIC_OP(uint64_t, uint64, u8, uint64_t, bxor)
    XBGAS_ATOMIC_OP(long long, longlong, s8, int64_t, bxor)
    XBGAS_ATOMIC_OP(int64_t, int64, s8, int64_t, bxor)

    /* Atomic min */
    XBGAS_ATOMIC_OP(unsigned int, uint, u4, uint32_t, min)
    XBGAS_ATOMIC_OP(unsigned long, ulong, u4, uint32_t, min)
    XBGAS_ATOMIC_OP(uint32_t, uint32, u4, uint32_t, min)
    XBGAS_ATOMIC_OP(int, int, s4, int32_t, min)
    XBGAS_ATOMIC_OP(long, long, s4, int32_t, min)
    XBGAS_ATOMIC_OP(int32_t, int32, s4, int32_t, min)
    XBGAS_ATOMIC_OP(unsigned long long, ulonglong, u8, uint64_t, min)
    XBGAS_ATOMIC_OP(uint64_t, uint64, u8, uint64_t, min)
    XBGAS_ATOMIC_OP(long long, longlong, s8, int64_t, min)
    XBGAS_ATOMIC_OP(int64_t, int64, s8, int64_t, min)

    /* Atomic max */
    XBGAS_ATOMIC_OP(unsigned int, uint, u4, uint32_t, max)
    XBGAS_ATOMIC_OP(unsigned long, ulong, u4, uint32_t, max)
    XBGAS_ATOMIC_OP(uint32_t, uint32, u4, uint32_t, max)
    XBGAS_ATOMIC_OP(int, int, s4, int32_t, max)
    XBGAS_ATOMIC_OP(long, long, s4, int32_t, max)
    XBGAS_ATOMIC_OP(int32_t, int32, s4, int32_t, max)
    XBGAS_ATOMIC_OP(unsigned long long, ulonglong, u8, uint64_t, max)
    XBGAS_ATOMIC_OP(uint64_t, uint64, u8, uint64_t, max)
    XBGAS_ATOMIC_OP(long long, longlong, s8, int64_t, max)
    XBGAS_ATOMIC_OP(int64_t, int64, s8, int64_t, max)

    /* Atomic compare and swap */
    XBGAS_ATOMIC_CAS(unsigned int, uint, u4, uint32_t)
    XBGAS_ATOMIC_CAS(unsigned long, ulong, u4, uint32_t)
    XBGAS_ATOMIC_CAS(uint32_t, uint32, u4, uint32_t)
    XBGAS_ATOMIC_CAS(int, int, s4, int32_t)
    XBGAS_ATOMIC_CAS(long, long, s4, int32_t)
    XBGAS_ATOMIC_CAS(int32_t, int32, s4, int32_t)
    XBGAS_ATOMIC_CAS(unsigned long long, ulonglong, u8, uint64_t)
    XBGAS_ATOMIC_CAS(uint64_t, uint64, u8, uint64_t)
    XBGAS_ATOMIC_CAS(long long, longlong, s8, int64_t)
    XBGAS_ATOMIC_CAS(int64_t, int64, s8, int64_t)

#undef XBGAS_ATOMIC_OP
#undef XBGAS_ATOMIC_CAS
