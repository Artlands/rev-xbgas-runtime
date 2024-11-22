/*
 * _XBRTIME_ALLTOALL_C_
 *
 * Copyright (C) 2017-2024  Tactical Computing Laboratories, LLC
 * All Rights Reserved
 * contact@tactcomplabs.com
 *
 * This file is a part of the XBGAS-RUNTIME package.  For license
 * information, see the LICENSE file in the top level directory
 * of the distribution.
 *
 */

#include "xbrtime.h"

#define ALLTOALLS_SHIFT_EXCHANGE(_type, _typename)                                                                                                   \
void xbrtime_##_typename##_alltoalls_shift_exchange(_type *dest, const _type *src, ptrdiff_t dest_stride, ptrdiff_t src_stride, size_t nelems)      \
{                                                                                                                                       \
    int i, my_rpe, numpes, total_elems;                                                                                                 \
    my_rpe = xbrtime_mype();                                                                                                            \
    numpes = xbrtime_num_pes();                                                                                                         \
    total_elems = numpes * nelems; /* Total elements per PE */                                                                          \
    _type *src_buff = (_type*) xbrtime_malloc(total_elems * sizeof(_type));                                                             \
    _type *dest_buff = (_type*) xbrtime_malloc(total_elems * sizeof(_type));                                                            \
                                                                                                                                        \
    /* Load src_buff */                                                                                                                 \
    for(i = 0; i < total_elems; i++)                                                                                                    \
    {                                                                                                                                   \
        src_buff[i] = src[i * src_stride];                                                                                              \
    }                                                                                                                                   \
                                                                                                                                        \
    xbrtime_barrier_all();                                                                                                              \
                                                                                                                                        \
    /* Perform put to dest_buff of each PE; Use partner = (my_rpe+i)%numpes to minimize network contention */                           \
    for(i = 0; i < numpes; i++)                                                                                                         \
    {                                                                                                                                   \
        xbrtime_##_typename##_put(&dest_buff[my_rpe*nelems], &src_buff[i*nelems], nelems, ((my_rpe+i)%numpes));                         \
    }                                                                                                                                   \
                                                                                                                                        \
    xbrtime_barrier_all();                                                                                                              \
                                                                                                                                        \
    /* Copy to dest with stride */                                                                                                      \
    for(i = 0; i < total_elems; i++)                                                                                                    \
    {                                                                                                                                   \
        dest[i * dest_stride] = dest_buff[i];                                                                                           \
    }                                                                                                                                   \
                                                                                                                                        \
    xbrtime_free(src_buff);                                                                                                             \
    xbrtime_free(dest_buff);                                                                                                            \
}                                                                                                                                       

    ALLTOALLS_SHIFT_EXCHANGE(float, float)
    ALLTOALLS_SHIFT_EXCHANGE(double, double)
    ALLTOALLS_SHIFT_EXCHANGE(char, char)
    ALLTOALLS_SHIFT_EXCHANGE(unsigned char, uchar)
    ALLTOALLS_SHIFT_EXCHANGE(signed char, schar)
    ALLTOALLS_SHIFT_EXCHANGE(unsigned short, ushort)
    ALLTOALLS_SHIFT_EXCHANGE(short, short)
    ALLTOALLS_SHIFT_EXCHANGE(unsigned int, uint)
    ALLTOALLS_SHIFT_EXCHANGE(int, int)
    ALLTOALLS_SHIFT_EXCHANGE(unsigned long, ulong)
    ALLTOALLS_SHIFT_EXCHANGE(long, long)
    ALLTOALLS_SHIFT_EXCHANGE(unsigned long long, ulonglong)
    ALLTOALLS_SHIFT_EXCHANGE(long long, longlong)
    ALLTOALLS_SHIFT_EXCHANGE(uint8_t, uint8)
    ALLTOALLS_SHIFT_EXCHANGE(int8_t, int8)
    ALLTOALLS_SHIFT_EXCHANGE(uint16_t, uint16)
    ALLTOALLS_SHIFT_EXCHANGE(int16_t, int16)
    ALLTOALLS_SHIFT_EXCHANGE(uint32_t, uint32)
    ALLTOALLS_SHIFT_EXCHANGE(int32_t, int32)
    ALLTOALLS_SHIFT_EXCHANGE(uint64_t, uint64)
    ALLTOALLS_SHIFT_EXCHANGE(int64_t, int64)
    ALLTOALLS_SHIFT_EXCHANGE(size_t, size)
    ALLTOALLS_SHIFT_EXCHANGE(ptrdiff_t, ptrdiff)

#undef ALLTOALLS_SHIFT_EXCHANGE


#define XBGAS_ALLTOALL(_type, _typename)                                                           \
/* Wrapper function - currently only support shift_exchange algorithm */                           \
void xbrtime_##_typename##_alltoall(_type *dest, const _type *src, size_t nelems)                  \
{                                                                                                  \
    return xbrtime_##_typename##_alltoalls_shift_exchange(dest, src, 1, 1, nelems);                \
}

    XBGAS_ALLTOALL(float, float)
    XBGAS_ALLTOALL(double, double)
    XBGAS_ALLTOALL(char, char)
    XBGAS_ALLTOALL(unsigned char, uchar)
    XBGAS_ALLTOALL(signed char, schar)
    XBGAS_ALLTOALL(unsigned short, ushort)
    XBGAS_ALLTOALL(short, short)
    XBGAS_ALLTOALL(unsigned int, uint)
    XBGAS_ALLTOALL(int, int)
    XBGAS_ALLTOALL(unsigned long, ulong)
    XBGAS_ALLTOALL(long, long)
    XBGAS_ALLTOALL(unsigned long long, ulonglong)
    XBGAS_ALLTOALL(long long, longlong)
    XBGAS_ALLTOALL(uint8_t, uint8)
    XBGAS_ALLTOALL(int8_t, int8)
    XBGAS_ALLTOALL(uint16_t, uint16)
    XBGAS_ALLTOALL(int16_t, int16)
    XBGAS_ALLTOALL(uint32_t, uint32)
    XBGAS_ALLTOALL(int32_t, int32)
    XBGAS_ALLTOALL(uint64_t, uint64)
    XBGAS_ALLTOALL(int64_t, int64)
    XBGAS_ALLTOALL(size_t, size)
    XBGAS_ALLTOALL(ptrdiff_t, ptrdiff)

#undef XBGAS_ALLTOALL

#define XBGAS_ALLTOALLS(_type, _typename)                                                                                               \
/* Wrapper function - currently only support shift_exchange algorithm */                                                                \
void xbrtime_##_typename##_alltoalls(_type *dest, const _type *src, ptrdiff_t dest_stride, ptrdiff_t src_stride, size_t nelems)         \
{                                                                                                                                       \
    return xbrtime_##_typename##_alltoalls_shift_exchange(dest, src, dest_stride, src_stride, nelems);                                  \
}

    XBGAS_ALLTOALLS(float, float)
    XBGAS_ALLTOALLS(double, double)
    XBGAS_ALLTOALLS(char, char)
    XBGAS_ALLTOALLS(unsigned char, uchar)
    XBGAS_ALLTOALLS(signed char, schar)
    XBGAS_ALLTOALLS(unsigned short, ushort)
    XBGAS_ALLTOALLS(short, short)
    XBGAS_ALLTOALLS(unsigned int, uint)
    XBGAS_ALLTOALLS(int, int)
    XBGAS_ALLTOALLS(unsigned long, ulong)
    XBGAS_ALLTOALLS(long, long)
    XBGAS_ALLTOALLS(unsigned long long, ulonglong)
    XBGAS_ALLTOALLS(long long, longlong)
    XBGAS_ALLTOALLS(uint8_t, uint8)
    XBGAS_ALLTOALLS(int8_t, int8)
    XBGAS_ALLTOALLS(uint16_t, uint16)
    XBGAS_ALLTOALLS(int16_t, int16)
    XBGAS_ALLTOALLS(uint32_t, uint32)
    XBGAS_ALLTOALLS(int32_t, int32)
    XBGAS_ALLTOALLS(uint64_t, uint64)
    XBGAS_ALLTOALLS(int64_t, int64)
    XBGAS_ALLTOALLS(size_t, size)
    XBGAS_ALLTOALLS(ptrdiff_t, ptrdiff)

#undef XBGAS_ALLTOALLS

/* EOF */
