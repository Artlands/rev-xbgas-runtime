/*
 * _XBRTIME_ATOMICS_C_
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

#include "xbrtime.h"

uint32_t xbrtime_decode_pe(int pe);
uint64_t __xbrtime_ltor(uint64_t remote,int pe);

/* ------------------------------------------------- FUNCTION PROTOTYPES */

int32_t __xbrtime_atomic_add_s4(uint64_t base_dest, int32_t value, uint32_t pe);
uint32_t __xbrtime_atomic_add_u4(uint64_t base_dest, uint32_t value, uint32_t pe);
int64_t __xbrtime_atomic_add_s8(uint64_t base_dest, int64_t value, uint32_t pe);
uint64_t __xbrtime_atomic_add_u8(uint64_t base_dest, uint64_t value, uint32_t pe);

int32_t __xbrtime_atomic_and_s4(uint64_t base_dest, int32_t value, uint32_t pe);
uint32_t __xbrtime_atomic_and_u4(uint64_t base_dest, uint32_t value, uint32_t pe);
int64_t __xbrtime_atomic_and_s8(uint64_t base_dest, int64_t value, uint32_t pe);
uint64_t __xbrtime_atomic_and_u8(uint64_t base_dest, uint64_t value, uint32_t pe);

int32_t __xbrtime_atomic_or_s4(uint64_t base_dest, int32_t value, uint32_t pe);
uint32_t __xbrtime_atomic_or_u4(uint64_t base_dest, uint32_t value, uint32_t pe);
int64_t __xbrtime_atomic_or_s8(uint64_t base_dest, int64_t value, uint32_t pe);
uint64_t __xbrtime_atomic_or_u8(uint64_t base_dest, uint64_t value, uint32_t pe);

int32_t __xbrtime_atomic_xor_s4(uint64_t base_dest, int32_t value, uint32_t pe);
uint32_t __xbrtime_atomic_xor_u4(uint64_t base_dest, uint32_t value, uint32_t pe);
int64_t __xbrtime_atomic_xor_s8(uint64_t base_dest, int64_t value, uint32_t pe);
uint64_t __xbrtime_atomic_xor_u8(uint64_t base_dest, uint64_t value, uint32_t pe);

int32_t __xbrtime_atomic_compare_swap_s4(uint64_t dest, int32_t cond, int32_t value, uint32_t pe);
uint32_t __xbrtime_atomic_compare_swap_u4(uint64_t dest, uint32_t cond, uint32_t value, uint32_t pe);
int64_t __xbrtime_atomic_compare_swap_s8(uint64_t dest, int64_t cond, int64_t value, uint32_t pe);
uint64_t __xbrtime_atomic_compare_swap_u8(uint64_t dest, uint64_t cond, uint64_t value, uint32_t pe);

uint32_t __xbrtime_atomic_fetch_4(uint64_t source, uint32_t pe);
uint64_t __xbrtime_atomic_fetch_8(uint64_t source, uint32_t pe);

void __xbrtime_atomic_set_s4(uint64_t dest, int32_t value, uint32_t pe);
void __xbrtime_atomic_set_u4(uint64_t dest, uint32_t value, uint32_t pe);
void __xbrtime_atomic_set_s8(uint64_t dest, int64_t value, uint32_t pe);
void __xbrtime_atomic_set_u8(uint64_t dest, uint64_t value, uint32_t pe);

int32_t __xbrtime_atomic_swap_s4(uint64_t dest, int32_t value, uint32_t pe);
uint32_t __xbrtime_atomic_swap_u4(uint64_t dest, uint32_t value, uint32_t pe);
int64_t __xbrtime_atomic_swap_s8(uint64_t dest, int64_t value, uint32_t pe);
uint64_t __xbrtime_atomic_swap_u8(uint64_t dest, uint64_t value, uint32_t pe);

uint32_t __xbrtime_atomic_fetch_inc_4(uint64_t dest, uint32_t pe);
uint64_t __xbrtime_atomic_fetch_inc_8(uint64_t dest, uint32_t pe);

void __xbrtime_atomic_inc_4(uint64_t dest, uint32_t pe);
void __xbrtime_atomic_inc_8(uint64_t dest, uint32_t pe);

int32_t __xbrtime_atomic_fetch_add_s4(uint64_t dest, int32_t value, uint32_t pe);
uint32_t __xbrtime_atomic_fetch_add_u4(uint64_t dest, uint32_t value, uint32_t pe);
int64_t __xbrtime_atomic_fetch_add_s8(uint64_t dest, int64_t value, uint32_t pe);
uint64_t __xbrtime_atomic_fetch_add_u8(uint64_t dest, uint64_t value, uint32_t pe);

int32_t __xbrtime_atomic_fetch_and_s4(uint64_t dest, int32_t value, uint32_t pe);
uint32_t __xbrtime_atomic_fetch_and_u4(uint64_t dest, uint32_t value, uint32_t pe);
int64_t __xbrtime_atomic_fetch_and_s8(uint64_t dest, int64_t value, uint32_t pe);
uint64_t __xbrtime_atomic_fetch_and_u8(uint64_t dest, uint64_t value, uint32_t pe);

int32_t __xbrtime_atomic_fetch_or_s4(uint64_t dest, int32_t value, uint32_t pe);
uint32_t __xbrtime_atomic_fetch_or_u4(uint64_t dest, uint32_t value, uint32_t pe);
int64_t __xbrtime_atomic_fetch_or_s8(uint64_t dest, int64_t value, uint32_t pe);
uint64_t __xbrtime_atomic_fetch_or_u8(uint64_t dest, uint64_t value, uint32_t pe);

int32_t __xbrtime_atomic_fetch_xor_s4(uint64_t dest, int32_t value, uint32_t pe);
uint32_t __xbrtime_atomic_fetch_xor_u4(uint64_t dest, uint32_t value, uint32_t pe);
int64_t __xbrtime_atomic_fetch_xor_s8(uint64_t dest, int64_t value, uint32_t pe);
uint64_t __xbrtime_atomic_fetch_xor_u8(uint64_t dest, uint64_t value, uint32_t pe);

#define XBGAS_ATOMIC_OP(_type, _typename, _typesize, _typecast, _op)                                                       \
_type xbrtime_##_typename##_atomic_##_op(_type *dest, _type value, int pe)                                                 \
{                                                                                                                          \
    return ((_type) __xbrtime_atomic_##_op##_##_typesize(__xbrtime_ltor(((uint64_t)dest), pe),                             \
                                                        (_typecast) value,                                                 \
                                                        xbrtime_decode_pe(pe)));                                           \
}

    /* Atomic add */
    XBGAS_ATOMIC_OP(int, int, s4, int32_t, add)
    XBGAS_ATOMIC_OP(long, long, s4, int32_t, add)
    XBGAS_ATOMIC_OP(long long, longlong, s8, int64_t, add)
    XBGAS_ATOMIC_OP(unsigned int, uint, u4, uint32_t, add)
    XBGAS_ATOMIC_OP(unsigned long, ulong, u4, uint32_t, add)
    XBGAS_ATOMIC_OP(unsigned long long, ulonglong, u8, uint64_t, add)
    XBGAS_ATOMIC_OP(int32_t, int32, s4, int32_t, add)
    XBGAS_ATOMIC_OP(uint32_t, uint32, u4, uint32_t, add)
    XBGAS_ATOMIC_OP(int64_t, int64, s8, int64_t, add)
    XBGAS_ATOMIC_OP(uint64_t, uint64, u8, uint64_t, add)
    XBGAS_ATOMIC_OP(size_t, size, u8, size_t, add)
    XBGAS_ATOMIC_OP(ptrdiff_t, ptrdiff, u8, ptrdiff_t, add)

    /* Atomic logical and */
    XBGAS_ATOMIC_OP(unsigned int, uint, u4, uint32_t, and)
    XBGAS_ATOMIC_OP(unsigned long, ulong, u4, uint32_t, and)
    XBGAS_ATOMIC_OP(unsigned long long, ulonglong, u8, uint64_t, and)
    XBGAS_ATOMIC_OP(int32_t, int32, s4, int32_t, and)
    XBGAS_ATOMIC_OP(uint32_t, uint32, u4, uint32_t, and)
    XBGAS_ATOMIC_OP(int64_t, int64, s8, int64_t, and)
    XBGAS_ATOMIC_OP(uint64_t, uint64, u8, uint64_t, and)

    /* Atomic logical or */
    XBGAS_ATOMIC_OP(unsigned int, uint, u4, uint32_t, or)
    XBGAS_ATOMIC_OP(unsigned long, ulong, u4, uint32_t, or)
    XBGAS_ATOMIC_OP(unsigned long long, ulonglong, u8, uint64_t, or)
    XBGAS_ATOMIC_OP(int32_t, int32, s4, int32_t, or)
    XBGAS_ATOMIC_OP(uint32_t, uint32, u4, uint32_t, or)
    XBGAS_ATOMIC_OP(int64_t, int64, s8, int64_t, or)
    XBGAS_ATOMIC_OP(uint64_t, uint64, u8, uint64_t, or)

    /* Atomic logical exclusive or */
    XBGAS_ATOMIC_OP(unsigned int, uint, u4, uint32_t, xor)
    XBGAS_ATOMIC_OP(unsigned long, ulong, u4, uint32_t, xor)
    XBGAS_ATOMIC_OP(unsigned long long, ulonglong, u8, uint64_t, xor)
    XBGAS_ATOMIC_OP(int32_t, int32, s4, int32_t, xor)
    XBGAS_ATOMIC_OP(uint32_t, uint32, u4, uint32_t, xor)
    XBGAS_ATOMIC_OP(int64_t, int64, s8, int64_t, xor)
    XBGAS_ATOMIC_OP(uint64_t, uint64, u8, uint64_t, xor)

#undef XBGAS_ATOMIC_OP

#define XBGAS_ATOMIC_FETCH(_type, _typename, _typesize)                                                                     \
_type xbrtime_##_typename##_atomic_fetch(_type *source, int pe)                                                             \
{                                                                                                                           \   
    return ((_type) __xbrtime_atomic_fetch_##_typesize(__xbrtime_ltor(((uint64_t)source), pe), xbrtime_decode_pe(pe)));     \    
}

    /* Atomic fetch */
    XBGAS_ATOMIC_FETCH(float, float, 4)
    XBGAS_ATOMIC_FETCH(double, double, 8)
    XBGAS_ATOMIC_FETCH(int, int, 4)
    XBGAS_ATOMIC_FETCH(long, long, 4)
    XBGAS_ATOMIC_FETCH(long long, longlong, 8)
    XBGAS_ATOMIC_FETCH(unsigned int, uint, 4)
    XBGAS_ATOMIC_FETCH(unsigned long, ulong, 4)
    XBGAS_ATOMIC_FETCH(unsigned long long, ulonglong, 8)
    XBGAS_ATOMIC_FETCH(int32_t, int32, 4)
    XBGAS_ATOMIC_FETCH(int64_t, int64, 8)
    XBGAS_ATOMIC_FETCH(uint32_t, uint32, 4)
    XBGAS_ATOMIC_FETCH(uint64_t, uint64, 8)
    XBGAS_ATOMIC_FETCH(size_t, size, 8)
    XBGAS_ATOMIC_FETCH(ptrdiff_t, ptrdiff, 8)

#undef XBGAS_ATOMIC_FETCH

#define XBGAS_ATOMIC_SET(_type, _typename, _typesize, _typecast)                                                                     \
void xbrtime_##_typename##_atomic_set(_type *dest, _type value, int pe)                                                              \
{                                                                                                                                    \   
    return ((void) __xbrtime_atomic_set_##_typesize(__xbrtime_ltor(((uint64_t)dest), pe), (_typecast)value, xbrtime_decode_pe(pe))); \    
}

    /* Atomic set */
    XBGAS_ATOMIC_SET(float, float, u4, uint32_t)
    XBGAS_ATOMIC_SET(double, double, u8, uint64_t)
    XBGAS_ATOMIC_SET(int, int, s4, int32_t)
    XBGAS_ATOMIC_SET(long, long, s4, int32_t)
    XBGAS_ATOMIC_SET(long long, longlong, s8, int64_t)
    XBGAS_ATOMIC_SET(unsigned int, uint, u4, uint32_t)
    XBGAS_ATOMIC_SET(unsigned long, ulong, u4, uint32_t)
    XBGAS_ATOMIC_SET(unsigned long long, ulonglong, u8, uint64_t)
    XBGAS_ATOMIC_SET(int32_t, int32, s4, int32_t)
    XBGAS_ATOMIC_SET(int64_t, int64, s8, int64_t)
    XBGAS_ATOMIC_SET(uint32_t, uint32, u4, uint32_t)
    XBGAS_ATOMIC_SET(uint64_t, uint64, u8, uint64_t)
    XBGAS_ATOMIC_SET(size_t, size, u8, size_t)
    XBGAS_ATOMIC_SET(ptrdiff_t, ptrdiff, u8, ptrdiff_t)

#undef XBGAS_ATOMIC_SET


#define XBGAS_ATOMIC_CAS(_type, _typename, _typesize, _typecast)                                                            \
_type xbrtime_##_typename##_atomic_compare_swap(_type *dest, _type cond, _type value, int pe)                               \
{                                                                                                                           \
    return ((_type) __xbrtime_atomic_compare_swap_##_typesize(__xbrtime_ltor(((uint64_t)dest), pe),                         \
                                                             (_typecast) cond,                                              \
                                                             (_typecast) value,                                             \
                                                             xbrtime_decode_pe(pe)));                                       \
}

    /* Atomic compare and swap */
    XBGAS_ATOMIC_CAS(int, int, s4, int32_t)
    XBGAS_ATOMIC_CAS(long, long, s4, int32_t)
    XBGAS_ATOMIC_CAS(long long, longlong, s8, int64_t)
    XBGAS_ATOMIC_CAS(unsigned int, uint, u4, uint32_t)
    XBGAS_ATOMIC_CAS(unsigned long, ulong, u4, uint32_t)
    XBGAS_ATOMIC_CAS(unsigned long long, ulonglong, u8, uint64_t)
    XBGAS_ATOMIC_CAS(int32_t, int32, s4, int32_t)
    XBGAS_ATOMIC_CAS(int64_t, int64, s8, int64_t)
    XBGAS_ATOMIC_CAS(uint32_t, uint32, u4, uint32_t)
    XBGAS_ATOMIC_CAS(uint64_t, uint64, u8, uint64_t)
    XBGAS_ATOMIC_CAS(size_t, size, u8, size_t)
    XBGAS_ATOMIC_CAS(ptrdiff_t, ptrdiff, u8, ptrdiff_t)

#undef XBGAS_ATOMIC_CAS

#define XBGAS_ATOMIC_SWAP(_type, _typename, _typesize, _typecast)                                                                      \
_type xbrtime_##_typename##_atomic_swap(_type *dest, _type value, int pe)                                                              \
{                                                                                                                                      \   
    return ((_type) __xbrtime_atomic_swap_##_typesize(__xbrtime_ltor(((uint64_t)dest), pe), (_typecast)value, xbrtime_decode_pe(pe))); \    
}

    /* Atomic swap */
    XBGAS_ATOMIC_SWAP(float, float, u4, uint32_t)
    XBGAS_ATOMIC_SWAP(double, double, u8, uint64_t)
    XBGAS_ATOMIC_SWAP(int, int, s4, int32_t)
    XBGAS_ATOMIC_SWAP(long, long, s4, int32_t)
    XBGAS_ATOMIC_SWAP(long long, longlong, s8, int64_t)
    XBGAS_ATOMIC_SWAP(unsigned int, uint, u4, uint32_t)
    XBGAS_ATOMIC_SWAP(unsigned long, ulong, u4, uint32_t)
    XBGAS_ATOMIC_SWAP(unsigned long long, ulonglong, u8, uint64_t)
    XBGAS_ATOMIC_SWAP(int32_t, int32, s4, int32_t)
    XBGAS_ATOMIC_SWAP(int64_t, int64, s8, int64_t)
    XBGAS_ATOMIC_SWAP(uint32_t, uint32, u4, uint32_t)
    XBGAS_ATOMIC_SWAP(uint64_t, uint64, u8, uint64_t)
    XBGAS_ATOMIC_SWAP(size_t, size, u8, size_t)
    XBGAS_ATOMIC_SWAP(ptrdiff_t, ptrdiff, u8, ptrdiff_t)

#undef XBGAS_ATOMIC_SWAP

#define XBGAS_ATOMIC_FETCH_INC(_type, _typename, _typesize)                                                                 \
_type xbrtime_##_typename##_atomic_fetch_inc(_type *dest, int pe)                                                           \
{                                                                                                                           \   
    return ((_type) __xbrtime_atomic_fetch_inc_##_typesize(__xbrtime_ltor(((uint64_t)dest), pe), xbrtime_decode_pe(pe)));   \    
}

    /* Atomic fetch-and-increment*/
    XBGAS_ATOMIC_FETCH_INC(int, int, 4)
    XBGAS_ATOMIC_FETCH_INC(long, long, 4)
    XBGAS_ATOMIC_FETCH_INC(long long, longlong, 8)
    XBGAS_ATOMIC_FETCH_INC(unsigned int, uint, 4)
    XBGAS_ATOMIC_FETCH_INC(unsigned long, ulong, 4)
    XBGAS_ATOMIC_FETCH_INC(unsigned long long, ulonglong, 8)
    XBGAS_ATOMIC_FETCH_INC(int32_t, int32, 4)
    XBGAS_ATOMIC_FETCH_INC(int64_t, int64, 8)
    XBGAS_ATOMIC_FETCH_INC(uint32_t, uint32, 4)
    XBGAS_ATOMIC_FETCH_INC(uint64_t, uint64, 8)
    XBGAS_ATOMIC_FETCH_INC(size_t, size, 8)
    XBGAS_ATOMIC_FETCH_INC(ptrdiff_t, ptrdiff, 8)

#undef XBGAS_ATOMIC_FETCH_INC

#define XBGAS_ATOMIC_INC(_type, _typename, _typesize)                                                                \
void xbrtime_##_typename##_atomic_inc(_type *dest, int pe)                                                           \
{                                                                                                                    \   
    return ((void) __xbrtime_atomic_inc_##_typesize(__xbrtime_ltor(((uint64_t)dest), pe), xbrtime_decode_pe(pe)));   \    
}

    /* Atomic increment*/
    XBGAS_ATOMIC_INC(int, int, 4)
    XBGAS_ATOMIC_INC(long, long, 4)
    XBGAS_ATOMIC_INC(long long, longlong, 8)
    XBGAS_ATOMIC_INC(unsigned int, uint, 4)
    XBGAS_ATOMIC_INC(unsigned long, ulong, 4)
    XBGAS_ATOMIC_INC(unsigned long long, ulonglong, 8)
    XBGAS_ATOMIC_INC(int32_t, int32, 4)
    XBGAS_ATOMIC_INC(int64_t, int64, 8)
    XBGAS_ATOMIC_INC(uint32_t, uint32, 4)
    XBGAS_ATOMIC_INC(uint64_t, uint64, 8)
    XBGAS_ATOMIC_INC(size_t, size, 8)
    XBGAS_ATOMIC_INC(ptrdiff_t, ptrdiff, 8)

#undef XBGAS_ATOMIC_INC

#define XBGAS_ATOMIC_FETCH_OP(_type, _typename, _typesize, _typecast, _op)                                                                      \
_type xbrtime_##_typename##_atomic_fetch_##_op(_type *dest, _type value, int pe)                                                                \
{                                                                                                                                               \   
    return ((_type) __xbrtime_atomic_fetch_##_op##_##_typesize(__xbrtime_ltor(((uint64_t)dest), pe), (_typecast)value, xbrtime_decode_pe(pe))); \    
}

    /* Atomic fetch-and-add */
    XBGAS_ATOMIC_FETCH_OP(int, int, s4, int32_t, add)
    XBGAS_ATOMIC_FETCH_OP(long, long, s4, int32_t, add)
    XBGAS_ATOMIC_FETCH_OP(long long, longlong, s8, int64_t, add)
    XBGAS_ATOMIC_FETCH_OP(unsigned int, uint, u4, uint32_t, add)
    XBGAS_ATOMIC_FETCH_OP(unsigned long, ulong, u4, uint32_t, add)
    XBGAS_ATOMIC_FETCH_OP(unsigned long long, ulonglong, u8, uint64_t, add)
    XBGAS_ATOMIC_FETCH_OP(int32_t, int32, s4, int32_t, add)
    XBGAS_ATOMIC_FETCH_OP(int64_t, int64, s8, int64_t, add)
    XBGAS_ATOMIC_FETCH_OP(uint32_t, uint32, u4, uint32_t, add)
    XBGAS_ATOMIC_FETCH_OP(uint64_t, uint64, u8, uint64_t, add)
    XBGAS_ATOMIC_FETCH_OP(size_t, size, u8, size_t, add)
    XBGAS_ATOMIC_FETCH_OP(ptrdiff_t, ptrdiff, u8, ptrdiff_t, add)

    /* Atomic fetch-and-and */
    XBGAS_ATOMIC_FETCH_OP(unsigned int, uint, u4, uint32_t, and)
    XBGAS_ATOMIC_FETCH_OP(unsigned long, ulong, u4, uint32_t, and)
    XBGAS_ATOMIC_FETCH_OP(unsigned long long, ulonglong, u8, uint64_t, and)
    XBGAS_ATOMIC_FETCH_OP(int32_t, int32, s4, int32_t, and)
    XBGAS_ATOMIC_FETCH_OP(int64_t, int64, s8, int64_t, and)
    XBGAS_ATOMIC_FETCH_OP(uint32_t, uint32, u4, uint32_t, and)
    XBGAS_ATOMIC_FETCH_OP(uint64_t, uint64, u8, uint64_t, and)

    /* Atomic fetch-and-or */
    XBGAS_ATOMIC_FETCH_OP(unsigned int, uint, u4, uint32_t, or)
    XBGAS_ATOMIC_FETCH_OP(unsigned long, ulong, u4, uint32_t, or)
    XBGAS_ATOMIC_FETCH_OP(unsigned long long, ulonglong, u8, uint64_t, or)
    XBGAS_ATOMIC_FETCH_OP(int32_t, int32, s4, int32_t, or)
    XBGAS_ATOMIC_FETCH_OP(int64_t, int64, s8, int64_t, or)
    XBGAS_ATOMIC_FETCH_OP(uint32_t, uint32, u4, uint32_t, or)
    XBGAS_ATOMIC_FETCH_OP(uint64_t, uint64, u8, uint64_t, or)

    /* Atomic fetch-and-exclusive or */
    XBGAS_ATOMIC_FETCH_OP(unsigned int, uint, u4, uint32_t, xor)
    XBGAS_ATOMIC_FETCH_OP(unsigned long, ulong, u4, uint32_t, xor)
    XBGAS_ATOMIC_FETCH_OP(unsigned long long, ulonglong, u8, uint64_t, xor)
    XBGAS_ATOMIC_FETCH_OP(int32_t, int32, s4, int32_t, xor)
    XBGAS_ATOMIC_FETCH_OP(int64_t, int64, s8, int64_t, xor)
    XBGAS_ATOMIC_FETCH_OP(uint32_t, uint32, u4, uint32_t, xor)
    XBGAS_ATOMIC_FETCH_OP(uint64_t, uint64, u8, uint64_t, xor)

#undef XBGAS_ATOMIC_FETCH_OP

/* EOF */
