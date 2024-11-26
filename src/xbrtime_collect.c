/*
 * _XBRTIME_COLLECT_C_
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

#define COLLECT_ALGORITHMS(_type, _typename)                                                                                            \
int xbrtime_##_typename##_collect_exchange(_type *dest, const _type *src, size_t nelems)                                                \
{                                                                                                                                       \
    int i, my_rpe, numpes;                                                                                                              \
    my_rpe = xbrtime_mype();                                                                                                            \
    numpes = xbrtime_num_pes();                                                                                                         \
                                                                                                                                        \
    /* Perform put to dest_buff of each PE; Use partner = (my_rpe+i)%numpes to minimize network contention */                           \
    for(i = 0; i < numpes; i++)                                                                                                         \
    {                                                                                                                                   \
        xbrtime_##_typename##_put(&dest[my_rpe*nelems], src, nelems, ((my_rpe+i)%numpes));                                              \
    }                                                                                                                                   \
    xbrtime_barrier_all();                                                                                                              \
    return 0;                                                                                                                           \
} 

    COLLECT_ALGORITHMS(float, float)
    COLLECT_ALGORITHMS(double, double)
    COLLECT_ALGORITHMS(char, char)
    COLLECT_ALGORITHMS(unsigned char, uchar)
    COLLECT_ALGORITHMS(signed char, schar)
    COLLECT_ALGORITHMS(unsigned short, ushort)
    COLLECT_ALGORITHMS(short, short)
    COLLECT_ALGORITHMS(unsigned int, uint)
    COLLECT_ALGORITHMS(int, int)
    COLLECT_ALGORITHMS(unsigned long, ulong)
    COLLECT_ALGORITHMS(long, long)
    COLLECT_ALGORITHMS(unsigned long long, ulonglong)
    COLLECT_ALGORITHMS(long long, longlong)
    COLLECT_ALGORITHMS(uint8_t, uint8)
    COLLECT_ALGORITHMS(int8_t, int8)
    COLLECT_ALGORITHMS(uint16_t, uint16)
    COLLECT_ALGORITHMS(int16_t, int16)
    COLLECT_ALGORITHMS(uint32_t, uint32)
    COLLECT_ALGORITHMS(int32_t, int32)
    COLLECT_ALGORITHMS(uint64_t, uint64)
    COLLECT_ALGORITHMS(int64_t, int64)
    COLLECT_ALGORITHMS(size_t, size)
    COLLECT_ALGORITHMS(ptrdiff_t, ptrdiff)
    
#undef COLLECT_ALGORITHMS


#define XBGAS_COLLECT(_type, _typename)                                                                                                 \
/* Wrapper function - only single algorithm used for collect at present */                                                              \
int xbrtime_##_typename##_collect(_type *dest, const _type *src, size_t nelems)                                                         \
{                                                                                                                                       \
    return xbrtime_##_typename##_collect_exchange(dest, src, nelems);                                                                   \
}                                                                                                                                       \
                                                                                                                                        \
int xbrtime_##_typename##_fcollect(_type *dest, const _type *src, size_t nelems)                                                        \
{                                                                                                                                       \
    return xbrtime_##_typename##_collect_exchange(dest, src, nelems);                                                                   \
}

    XBGAS_COLLECT(float, float)
    XBGAS_COLLECT(double, double)
    XBGAS_COLLECT(char, char)
    XBGAS_COLLECT(unsigned char, uchar)
    XBGAS_COLLECT(signed char, schar)
    XBGAS_COLLECT(unsigned short, ushort)
    XBGAS_COLLECT(short, short)
    XBGAS_COLLECT(unsigned int, uint)
    XBGAS_COLLECT(int, int)
    XBGAS_COLLECT(unsigned long, ulong)
    XBGAS_COLLECT(long, long)
    XBGAS_COLLECT(unsigned long long, ulonglong)
    XBGAS_COLLECT(long long, longlong)
    XBGAS_COLLECT(uint8_t, uint8)
    XBGAS_COLLECT(int8_t, int8)
    XBGAS_COLLECT(uint16_t, uint16)
    XBGAS_COLLECT(int16_t, int16)
    XBGAS_COLLECT(uint32_t, uint32)
    XBGAS_COLLECT(int32_t, int32)
    XBGAS_COLLECT(uint64_t, uint64)
    XBGAS_COLLECT(int64_t, int64)
    XBGAS_COLLECT(size_t, size)
    XBGAS_COLLECT(ptrdiff_t, ptrdiff)

#undef XBGAS_COLLECT

/* EOF */
