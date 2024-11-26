/*
 * _XBRTIME_BROADCAST_C_
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

#define BROADCAST_ALGORITHMS(_type, _typename)                                                                             \
int xbrtime_##_typename##_broadcast_tree(_type *dest, const _type *src, size_t nelems, int root)                           \
{                                                                                                                          \
    int i, numpes, my_rpe, my_vpe, numpes_log, mask, two_i, r_partner, v_partner;                                          \
    numpes = xbrtime_num_pes();                                                                                            \
    my_rpe = xbrtime_mype();                                                                                               \
    my_vpe = ((my_rpe >= root) ? (my_rpe - root) : (my_rpe + numpes - root));                                              \
    _type *temp = (_type*) xbrtime_malloc(sizeof(_type) * nelems);							                               \
    numpes_log = (int) ceil((log(numpes)/log(2)));  /* Number of commmuication stages */                                   \
    mask = (int) (pow(2,numpes_log) - 1);                                                                                  \
                                                                                                                           \
    /* Root load values into buffer without stride */									                                   \
    if(my_rpe == root)													                                                   \
    {															                                                           \
    for(i = 0; i < nelems; i++)											                                                   \
    {														                                                               \
        temp[i] = src[i];											                                                       \
    }														                                                               \
    }															                                                           \
                                                                                                                           \
    /* Perform communication if PE active at stage i and has valid partner */                                              \
    for(i = numpes_log-1; i >= 0; i--)                                                                                     \
    {                                                                                                                      \
        two_i = (int) pow(2,i);                                                                                            \
        mask = mask ^ two_i;                                                                                               \
        if(((my_vpe & mask) == 0) && ((my_vpe & two_i) == 0))                                                              \
        {                                                                                                                  \
            v_partner = (my_vpe ^ two_i) % numpes;                                                                         \
            r_partner = (v_partner + root) % numpes;                                                                       \
            if(my_vpe < v_partner)                                                                                         \
            {                                                                                                              \
                xbrtime_##_typename##_put(temp, temp, nelems, r_partner);                                                  \
            }                                                                                                              \
        }                                                                                                                  \
        xbrtime_barrier_all();                                                                                             \
    }                                                                                                                      \
                                                                                                                           \
    /* Migrate from buffer to dest with stride */                                                                          \
    for(i = 0; i < nelems; i++)                                                                                            \
    {                                                                                                                      \
        dest[i] = temp[i];                                                                                                 \
    }                                                                                                                      \
    xbrtime_free(temp);                                                                                                    \
    return 0;                                                                                                              \
}                                                                                                                                                                                                                                                 

    BROADCAST_ALGORITHMS(float, float)
    BROADCAST_ALGORITHMS(double, double)
    BROADCAST_ALGORITHMS(char, char)
    BROADCAST_ALGORITHMS(unsigned char, uchar)
    BROADCAST_ALGORITHMS(signed char, schar)
    BROADCAST_ALGORITHMS(unsigned short, ushort)
    BROADCAST_ALGORITHMS(short, short)
    BROADCAST_ALGORITHMS(unsigned int, uint)
    BROADCAST_ALGORITHMS(int, int)
    BROADCAST_ALGORITHMS(unsigned long, ulong)
    BROADCAST_ALGORITHMS(long, long)
    BROADCAST_ALGORITHMS(unsigned long long, ulonglong)
    BROADCAST_ALGORITHMS(long long, longlong)
    BROADCAST_ALGORITHMS(uint8_t, uint8)
    BROADCAST_ALGORITHMS(int8_t, int8)
    BROADCAST_ALGORITHMS(uint16_t, uint16)
    BROADCAST_ALGORITHMS(int16_t, int16)
    BROADCAST_ALGORITHMS(uint32_t, uint32)
    BROADCAST_ALGORITHMS(int32_t, int32)
    BROADCAST_ALGORITHMS(uint64_t, uint64)
    BROADCAST_ALGORITHMS(int64_t, int64)
    BROADCAST_ALGORITHMS(size_t, size)
    BROADCAST_ALGORITHMS(ptrdiff_t, ptrdiff)

#undef BROADCAST_ALGORITHMS

 #define XBGAS_BROADCAST(_type, _typename)                                                                                 \
 /* Wrapper function - binomial tree for small messages, van de geijn for large messages */                                \
 int xbrtime_##_typename##_broadcast(_type *dest, const _type *src, size_t nelems, int root)                               \
 {                                                                                                                         \
    return xbrtime_##_typename##_broadcast_tree(dest, src, nelems, root);                                                  \
 }

    XBGAS_BROADCAST(float, float)
    XBGAS_BROADCAST(double, double)
    XBGAS_BROADCAST(char, char)
    XBGAS_BROADCAST(unsigned char, uchar)
    XBGAS_BROADCAST(signed char, schar)
    XBGAS_BROADCAST(unsigned short, ushort)
    XBGAS_BROADCAST(short, short)
    XBGAS_BROADCAST(unsigned int, uint)
    XBGAS_BROADCAST(int, int)
    XBGAS_BROADCAST(unsigned long, ulong)
    XBGAS_BROADCAST(long, long)
    XBGAS_BROADCAST(unsigned long long, ulonglong)
    XBGAS_BROADCAST(long long, longlong)
    XBGAS_BROADCAST(uint8_t, uint8)
    XBGAS_BROADCAST(int8_t, int8)
    XBGAS_BROADCAST(uint16_t, uint16)
    XBGAS_BROADCAST(int16_t, int16)
    XBGAS_BROADCAST(uint32_t, uint32)
    XBGAS_BROADCAST(int32_t, int32)
    XBGAS_BROADCAST(uint64_t, uint64)
    XBGAS_BROADCAST(int64_t, int64)
    XBGAS_BROADCAST(size_t, size)
    XBGAS_BROADCAST(ptrdiff_t, ptrdiff)

#undef XBGAS_BROADCAST

/* EOF */
