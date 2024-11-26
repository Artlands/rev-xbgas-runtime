/*
 * _XBRTIME_REDUCTION_C_
 *
 * Copyright (C) 2017-2024 Tactical Computing Laboratories, LLC
 * All Rights Reserved
 * contact@tactcomplabs.com
 *
 * This file is a part of the XBGAS-RUNTIME package.  For license
 * information, see the LICENSE file in the top level directory
 * of the distribution.
 *
 */

#include "xbrtime.h"

/* For use with min/max reduction */
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define REDUCTION_ALGORITHMS(_type, _typename, _funcname, _op)                                                                                          \
int xbrtime_##_typename##_funcname##_recursive_doubling(_type *dest, const _type *src, size_t nreduce)                                                  \
{                                                                                                                                                       \
    int i, j, numpes, my_rpe, my_vpe, r_partner, numpes_log_floor, p_prime, remainder;                                                                  \
    numpes = xbrtime_num_pes();                                                                                                                         \
    my_rpe = xbrtime_mype();                                                                                                                            \
    my_vpe = my_rpe;                                                                                                                                    \
    numpes_log_floor = (int) (log(numpes)/log(2));                                                                                                      \
    p_prime = 1 << numpes_log_floor;                                                                                                                    \
    remainder = numpes - p_prime;                                                                                                                       \
    _type *accumulate = (_type*) xbrtime_malloc(sizeof(_type) * nreduce);                                                                               \
    _type *temp = (_type*) xbrtime_malloc(sizeof(_type) * nreduce);                                                                                     \
                                                                                                                                                        \
    /* Load reduction values into accumulate buffer */                                                                                                  \
    for(i = 0; i < nreduce; i++)                                                                                                                        \
    {                                                                                                                                                   \
        accumulate[i] = src[i];                                                                                                                         \
    }                                                                                                                                                   \
                                                                                                                                                        \
    /* Ensure buffer is ready */                                                                                                                        \
    xbrtime_barrier_all();                                                                                                                              \
                                                                                                                                                        \
    /* Stage 1 (only if NumPEs is not a power of two) */                                                                                                \
    if(numpes_log_floor != (log(numpes)/log(2)))                                                                                                        \
    {                                                                                                                                                   \
        /* First 2r ranks */                                                                                                                            \
        if(my_rpe < 2*remainder)                                                                                                                        \
        {                                                                                                                                               \
            /* Even ranks */                                                                                                                            \
            if(my_rpe % 2 == 0)                                                                                                                         \
            {                                                                                                                                           \
                /* Get values from my_rpe + 1 */                                                                                                        \
                xbrtime_##_typename##_get(temp, accumulate, nreduce, my_rpe + 1);                                                                       \
                                                                                                                                                        \
                /* Perform reduction op */                                                                                                              \
                for(j = 0; j < nreduce; j++)                                                                                                            \
                {                                                                                                                                       \
                    accumulate[j] = accumulate[j] _op temp[j];                                                                                          \
                }                                                                                                                                       \
                                                                                                                                                        \
                /* Assign new vpe ranks */                                                                                                              \
                my_vpe = my_rpe/2;                                                                                                                      \
            }                                                                                                                                           \
            /* Odd ranks */                                                                                                                             \
            else                                                                                                                                        \
            {                                                                                                                                           \
                /* Assign new vpe ranks */                                                                                                              \
                my_vpe = -1;                                                                                                                            \
            }                                                                                                                                           \
        }                                                                                                                                               \
        else                                                                                                                                            \
        {                                                                                                                                               \
            /* Assign new vpe ranks */                                                                                                                  \
            my_vpe = my_rpe - remainder;                                                                                                                \
        }                                                                                                                                               \
        xbrtime_barrier_all();                                                                                                                          \
    }                                                                                                                                                   \
                                                                                                                                                        \
    /* Stage 2 - Recursive Doubling */                                                                                                                  \
    int pe_stride = 1;                                                                                                                                  \
    for(i = 0; i < numpes_log_floor; i++)                                                                                                               \
    {                                                                                                                                                   \
        if(my_vpe != -1)                                                                                                                                \
        {                                                                                                                                               \
            if((my_vpe & ( 1 << i)) == 0)                                                                                                               \
            {                                                                                                                                           \
                /* Get from my_vpe + stride */                                                                                                          \
                r_partner = ((my_vpe+pe_stride) < remainder ? (my_vpe+pe_stride)*2 : (my_vpe+pe_stride)+remainder);                                     \
            }                                                                                                                                           \
            else                                                                                                                                        \
            {                                                                                                                                           \
                /* Get from my_vpe - stride */                                                                                                          \
                r_partner = (((my_vpe-pe_stride+p_prime)%p_prime) < remainder ? ((my_vpe-pe_stride+p_prime)%p_prime)*2 :                                \
                            ((my_vpe-pe_stride+p_prime)%p_prime)+remainder);                                                                            \
            }                                                                                                                                           \
                                                                                                                                                        \
            xbrtime_##_typename##_get(temp, accumulate, nreduce, r_partner);                                                                            \
        }                                                                                                                                               \
        /* Ensure get is complete */                                                                                                                    \
        xbrtime_barrier_all();                                                                                                                          \
                                                                                                                                                        \
        /* Perform reduction op */                                                                                                                      \
        if(my_vpe != -1)                                                                                                                                \
        {                                                                                                                                               \
            for(j = 0; j < nreduce; j++)                                                                                                                \
            {                                                                                                                                           \
                accumulate[j] = accumulate[j] _op temp[j];                                                                                              \
            }                                                                                                                                           \
        }                                                                                                                                               \
        pe_stride <<= 1;                                                                                                                                \
        xbrtime_barrier_all();                                                                                                                          \
    }                                                                                                                                                   \
                                                                                                                                                        \
    /* Put all reduced values to remainder PEs if not a power of two */                                                                                 \
    if(numpes_log_floor != (log(numpes)/log(2)))                                                                                                        \
    {                                                                                                                                                   \
        /* First r even rpe ranks*/                                                                                                                     \
        if((my_rpe < 2*remainder) && (my_rpe % 2 == 0))                                                                                                 \
        {                                                                                                                                               \
            xbrtime_##_typename##_put(accumulate, accumulate, nreduce, my_rpe + 1);                                                                     \
        }                                                                                                                                               \
        xbrtime_barrier_all();                                                                                                                          \
    }                                                                                                                                                   \
                                                                                                                                                        \
    /* Copy from buffer to dest */                                                                                                                      \
    for(i = 0; i < nreduce; i++)                                                                                                                        \
    {                                                                                                                                                   \
        dest[i] = accumulate[i];                                                                                                                        \
    }                                                                                                                                                   \
                                                                                                                                                        \
    xbrtime_free(accumulate);                                                                                                                           \
    xbrtime_free(temp);                                                                                                                                 \
    return 0;                                                                                                                                           \
}                                                                                                                                                       \
                                                                                                                                                        \
int xbrtime_##_typename##_funcname##_rabenseifner(_type *dest, const _type *src, size_t nreduce)                                                        \
{                                                                                                                                                       \
    int i, j, numpes, my_rpe, my_vpe, r_partner, numpes_log_floor, p_prime, remainder, counter;                                                         \
    numpes = xbrtime_num_pes();                                                                                                                         \
    my_rpe = xbrtime_mype();                                                                                                                            \
    my_vpe = my_rpe;                                                                                                                                    \
    numpes_log_floor = (int) (log(numpes)/log(2));                                                                                                      \
    p_prime = 1 << numpes_log_floor;                                                                                                                    \
    remainder = numpes - p_prime;                                                                                                                       \
    _type *accumulate = (_type*) xbrtime_malloc(sizeof(_type) * nreduce);                                                                               \
    _type *temp = (_type*) xbrtime_malloc(sizeof(_type) * nreduce);                                                                                     \
                                                                                                                                                        \
    /* Load reduction values into accumulate buffer */                                                                                                  \
    for(i = 0; i < nreduce; i++)                                                                                                                        \
    {                                                                                                                                                   \
        accumulate[i] = src[i];                                                                                                                         \
    }                                                                                                                                                   \
                                                                                                                                                        \
    /* Divide buffers into p_prime partitions */                                                                                                        \
    counter = 0;                                                                                                                                        \
    int partition_sizes[p_prime], partition_disp[p_prime];                                                                                              \
    for(i = 0; i < p_prime; i++)                                                                                                                        \
    {                                                                                                                                                   \
        partition_sizes[i] = ( (i == p_prime-1) ?                                                                                                       \
                             (((int)(nreduce/p_prime)) + (nreduce%p_prime)) :                                                                           \
                             ((int)(nreduce/p_prime)) );                                                                                                \
        partition_disp[i] = counter;                                                                                                                    \
        counter += partition_sizes[i];                                                                                                                  \
    }                                                                                                                                                   \
                                                                                                                                                        \
    /* Ensure buffer is ready */                                                                                                                        \
    xbrtime_barrier_all();                                                                                                                              \
                                                                                                                                                        \
    int num_exchange = p_prime/2;                                                                                                                       \
    int msg_size = 0;                                                                                                                                   \
                                                                                                                                                        \
    /* Stage 1 - ReduceScatter (only if NumPEs is not a power of two) */                                                                                \
    if(numpes_log_floor != (log(numpes)/log(2)))                                                                                                        \
    {                                                                                                                                                   \
        /* First 2r ranks */                                                                                                                            \
        if(my_rpe < 2*remainder)                                                                                                                        \
        {                                                                                                                                               \
            /* Even ranks */                                                                                                                            \
            if(my_rpe % 2 == 0)                                                                                                                         \
            {                                                                                                                                           \
                /* Calculate and get first half of values from my_rpe + 1 */                                                                            \
                for(j = 0; j < num_exchange; j++)                                                                                                       \
                {                                                                                                                                       \
                    msg_size += partition_sizes[j];                                                                                                     \
                }                                                                                                                                       \
                                                                                                                                                        \
                xbrtime_##_typename##_get(temp, accumulate, msg_size, my_rpe + 1);                                                                      \
                                                                                                                                                        \
                /* Perform reduction op */                                                                                                              \
                for(j = 0; j < msg_size; j++)                                                                                                           \
                {                                                                                                                                       \
                    accumulate[j] = accumulate[j] _op temp[j];                                                                                          \
                }                                                                                                                                       \
                                                                                                                                                        \
                /* Assign new vpe ranks */                                                                                                              \
                my_vpe = my_rpe/2;                                                                                                                      \
            }                                                                                                                                           \
            /* Odd ranks */                                                                                                                             \
            else                                                                                                                                        \
            {                                                                                                                                           \
                /* Calculate and get second half of values from my_rpe - 1 */                                                                           \
                for(j = num_exchange; j < p_prime; j++)                                                                                                 \
                {                                                                                                                                       \
                    msg_size += partition_sizes[j];                                                                                                     \
                }                                                                                                                                       \
                                                                                                                                                        \
                xbrtime_##_typename##_get(&(temp[(partition_disp[num_exchange])]), &(accumulate[(partition_disp[num_exchange])]),                       \
                                            msg_size, my_rpe - 1);                                                                                      \
                                                                                                                                                        \
                /* Perform reduction op */                                                                                                              \
                for(j = 0; j < msg_size; j++)                                                                                                           \
                {                                                                                                                                       \
                    accumulate[(partition_disp[num_exchange])+j] = accumulate[(partition_disp[num_exchange])+j]                                         \
                                                                    _op temp[(partition_disp[num_exchange])+j];                                         \
                }                                                                                                                                       \
                                                                                                                                                        \
                /* Put calculated second half values back to even partner */                                                                            \
                xbrtime_##_typename##_put(&(accumulate[(partition_disp[num_exchange])]), &(accumulate[(partition_disp[num_exchange])]),                 \
                                            msg_size, my_rpe - 1);                                                                                      \
                                                                                                                                                        \
                /* Assign new vpe ranks */                                                                                                              \
                my_vpe = -1;                                                                                                                            \
            }                                                                                                                                           \
        }                                                                                                                                               \
        else                                                                                                                                            \
        {                                                                                                                                               \
            /* Assign new vpe ranks */                                                                                                                  \
            my_vpe = my_rpe - remainder;                                                                                                                \
        }                                                                                                                                               \
        xbrtime_barrier_all();                                                                                                                          \
    }                                                                                                                                                   \
                                                                                                                                                        \
    /* Stage 2 - ReduceScatter Recursive Doubling/Halving */                                                                                            \
    int pe_stride = 1;                                                                                                                                  \
    int offset = 0;                                                                                                                                     \
    for(i = 0; i < numpes_log_floor; i++)                                                                                                               \
    {                                                                                                                                                   \
        msg_size = 0;                                                                                                                                   \
        if(my_vpe != -1)                                                                                                                                \
        {                                                                                                                                               \
            /* PEs perform get and reduction of first buffer half */                                                                                    \
            if((my_vpe & ( 1 << i)) == 0)                                                                                                               \
            {                                                                                                                                           \
                r_partner = ((my_vpe+pe_stride) < remainder ? (my_vpe+pe_stride)*2 : (my_vpe+pe_stride)+remainder);                                     \
                                                                                                                                                        \
                /* Calculate msg_size */                                                                                                                \
                for(j = 0; j < num_exchange; j++)                                                                                                       \
                {                                                                                                                                       \
                    msg_size += partition_sizes[offset+j];                                                                                              \
                }                                                                                                                                       \
                                                                                                                                                        \
                xbrtime_##_typename##_get(&(temp[(partition_disp[offset])]), &(accumulate[(partition_disp[offset])]), msg_size, r_partner);             \
                                                                                                                                                        \
                /* Perform reduction op */                                                                                                              \
                for(j = 0; j < msg_size; j++)                                                                                                           \
                {                                                                                                                                       \
                    accumulate[(partition_disp[offset]+j)] = accumulate[(partition_disp[offset])+j] _op temp[(partition_disp[offset])+j];               \
                }                                                                                                                                       \
            }                                                                                                                                           \
            /* PEs perform get and reduction of second buffer half */                                                                                   \
            else                                                                                                                                        \
            {                                                                                                                                           \
                r_partner = (((my_vpe-pe_stride+p_prime)%p_prime) < remainder ? ((my_vpe-pe_stride+p_prime)%p_prime)*2 :                                \
                            ((my_vpe-pe_stride+p_prime)%p_prime)+remainder);                                                                            \
                                                                                                                                                        \
                /* Calculate msg_size */                                                                                                                \
                for(j = 0; j < num_exchange; j++)                                                                                                       \
                {                                                                                                                                       \
                    msg_size += partition_sizes[offset+num_exchange+j];                                                                                 \
                }                                                                                                                                       \
                                                                                                                                                        \
                xbrtime_##_typename##_get(&(temp[(partition_disp[offset+num_exchange])]), &(accumulate[(partition_disp[offset+num_exchange])]),         \
                                            msg_size, r_partner);                                                                                       \
                                                                                                                                                        \
                /* Perform reduction op */                                                                                                              \
                for(j = 0; j < msg_size; j++)                                                                                                           \
                {                                                                                                                                       \
                    accumulate[(partition_disp[offset+num_exchange])+j] = accumulate[(partition_disp[offset+num_exchange])+j]                           \
                                                                            _op temp[(partition_disp[offset+num_exchange])+j];                          \
                }                                                                                                                                       \
                                                                                                                                                        \
                /* Increase offset for these PEs*/                                                                                                      \
                offset += num_exchange;                                                                                                                 \
            }                                                                                                                                           \
        }                                                                                                                                               \
        num_exchange >>= 1;                                                                                                                             \
        pe_stride <<= 1;                                                                                                                                \
        xbrtime_barrier_all();                                                                                                                          \
    }                                                                                                                                                   \
                                                                                                                                                        \
    /* Stage 3 - GatherAll */                                                                                                                           \
    pe_stride = (1 << (numpes_log_floor-1));                                                                                                            \
    num_exchange = 1;                                                                                                                                   \
    for(i = numpes_log_floor - 1; i >= 0; i--)                                                                                                          \
    {                                                                                                                                                   \
        msg_size = 0;                                                                                                                                   \
        if(my_vpe != -1)                                                                                                                                \
        {                                                                                                                                               \
            /* PEs perform put */                                                                                                                       \
            if((my_vpe & ( 1 << i)) == 0)                                                                                                               \
            {                                                                                                                                           \
                r_partner = ((my_vpe+pe_stride) < remainder ? (my_vpe+pe_stride)*2 : (my_vpe+pe_stride)+remainder);                                     \
                                                                                                                                                        \
                /* Calculate msg_size */                                                                                                                \
                for(j = 0; j < num_exchange; j++)                                                                                                       \
                {                                                                                                                                       \
                    msg_size += partition_sizes[offset+j];                                                                                              \
                }                                                                                                                                       \
                                                                                                                                                        \
                xbrtime_##_typename##_put(&(accumulate[(partition_disp[offset])]), &(accumulate[(partition_disp[offset])]), msg_size, r_partner);       \
            }                                                                                                                                           \
            /* PEs perform put*/                                                                                                                        \
            else                                                                                                                                        \
            {                                                                                                                                           \
                r_partner = (((my_vpe-pe_stride+p_prime)%p_prime) < remainder ? ((my_vpe-pe_stride+p_prime)%p_prime)*2 :                                \
                            ((my_vpe-pe_stride+p_prime)%p_prime)+remainder);                                                                            \
                                                                                                                                                        \
                /* Decrease offset for these PEs*/                                                                                                      \
                offset -= num_exchange;                                                                                                                 \
                                                                                                                                                        \
                /* Calculate msg_size */                                                                                                                \
                for(j = 0; j < num_exchange; j++)                                                                                                       \
                {                                                                                                                                       \
                    msg_size += partition_sizes[offset+num_exchange+j];                                                                                 \
                }                                                                                                                                       \
                                                                                                                                                        \
                xbrtime_##_typename##_put(&(accumulate[(partition_disp[offset+num_exchange])]), &(accumulate[(partition_disp[offset+num_exchange])]),   \
                                          msg_size, r_partner);                                                                                         \
            }                                                                                                                                           \
        }                                                                                                                                               \
        num_exchange <<= 1;                                                                                                                             \
        pe_stride >>= 1;                                                                                                                                \
        xbrtime_barrier_all();                                                                                                                          \
    }                                                                                                                                                   \
                                                                                                                                                        \
    /* Put all reduced values to remainder PEs if not a power of two */                                                                                 \
    if(numpes_log_floor != (log(numpes)/log(2)))                                                                                                        \
    {                                                                                                                                                   \
        /* First r even rpe ranks*/                                                                                                                     \
        if((my_rpe < 2*remainder) && (my_rpe % 2 == 0))                                                                                                 \
        {                                                                                                                                               \
            xbrtime_##_typename##_put(accumulate, accumulate, nreduce, my_rpe + 1);                                                                     \
        }                                                                                                                                               \
        xbrtime_barrier_all();                                                                                                                          \
    }                                                                                                                                                   \
                                                                                                                                                        \
    /* Copy from buffer to dest with stride */                                                                                                          \
    for(i = 0; i < nreduce; i++)                                                                                                                        \
    {                                                                                                                                                   \
        dest[i] = accumulate[i];                                                                                                                        \
    }                                                                                                                                                   \
                                                                                                                                                        \
    xbrtime_free(accumulate);                                                                                                                           \
    xbrtime_free(temp);                                                                                                                                 \
    return 0;                                                                                                                                           \
}

    /* Sum */
    REDUCTION_ALGORITHMS(float, float, sum, +)
    REDUCTION_ALGORITHMS(double, double, sum, +)
    REDUCTION_ALGORITHMS(char, char, sum, +)
    REDUCTION_ALGORITHMS(unsigned char, uchar, sum, +)
    REDUCTION_ALGORITHMS(signed char, schar, sum, +)
    REDUCTION_ALGORITHMS(unsigned short, ushort, sum, +)
    REDUCTION_ALGORITHMS(short, short, sum, +)
    REDUCTION_ALGORITHMS(unsigned int, uint, sum, +)
    REDUCTION_ALGORITHMS(int, int, sum, +)
    REDUCTION_ALGORITHMS(unsigned long, ulong, sum, +)
    REDUCTION_ALGORITHMS(long, long, sum, +)
    REDUCTION_ALGORITHMS(unsigned long long, ulonglong, sum, +)
    REDUCTION_ALGORITHMS(long long, longlong, sum, +)
    REDUCTION_ALGORITHMS(uint8_t, uint8, sum, +)
    REDUCTION_ALGORITHMS(int8_t, int8, sum, +)
    REDUCTION_ALGORITHMS(uint16_t, uint16, sum, +)
    REDUCTION_ALGORITHMS(int16_t, int16, sum, +)
    REDUCTION_ALGORITHMS(uint32_t, uint32, sum, +)
    REDUCTION_ALGORITHMS(int32_t, int32, sum, +)
    REDUCTION_ALGORITHMS(uint64_t, uint64, sum, +)
    REDUCTION_ALGORITHMS(int64_t, int64, sum, +)
    REDUCTION_ALGORITHMS(size_t, size, sum, +)
    REDUCTION_ALGORITHMS(ptrdiff_t, ptrdiff, sum, +)

    /* Product */
    REDUCTION_ALGORITHMS(float, float, product, *)
    REDUCTION_ALGORITHMS(double, double, product, *)
    REDUCTION_ALGORITHMS(char, char, product, *)
    REDUCTION_ALGORITHMS(unsigned char, uchar, product, *)
    REDUCTION_ALGORITHMS(signed char, schar, product, *)
    REDUCTION_ALGORITHMS(unsigned short, ushort, product, *)
    REDUCTION_ALGORITHMS(short, short, product, *)
    REDUCTION_ALGORITHMS(unsigned int, uint, product, *)
    REDUCTION_ALGORITHMS(int, int, product, *)
    REDUCTION_ALGORITHMS(unsigned long, ulong, product, *)
    REDUCTION_ALGORITHMS(long, long, product, *)
    REDUCTION_ALGORITHMS(unsigned long long, ulonglong, product, *)
    REDUCTION_ALGORITHMS(long long, longlong, product, *)
    REDUCTION_ALGORITHMS(uint8_t, uint8, product, *)
    REDUCTION_ALGORITHMS(int8_t, int8, product, *)
    REDUCTION_ALGORITHMS(uint16_t, uint16, product, *)
    REDUCTION_ALGORITHMS(int16_t, int16, product, *)
    REDUCTION_ALGORITHMS(uint32_t, uint32, product, *)
    REDUCTION_ALGORITHMS(int32_t, int32, product, *)
    REDUCTION_ALGORITHMS(uint64_t, uint64, product, *)
    REDUCTION_ALGORITHMS(int64_t, int64, product, *)
    REDUCTION_ALGORITHMS(size_t, size, product, *)
    REDUCTION_ALGORITHMS(ptrdiff_t, ptrdiff, product, *)

    /* Binary AND */
    REDUCTION_ALGORITHMS(unsigned char, uchar, and, &)
    REDUCTION_ALGORITHMS(unsigned short, ushort, and, &)
    REDUCTION_ALGORITHMS(unsigned int, uint, and, &)
    REDUCTION_ALGORITHMS(unsigned long, ulong, and, &)
    REDUCTION_ALGORITHMS(unsigned long long, ulonglong, and, &)
    REDUCTION_ALGORITHMS(uint8_t, uint8, and, &)
    REDUCTION_ALGORITHMS(int8_t, int8, and, &)
    REDUCTION_ALGORITHMS(uint16_t, uint16, and, &)
    REDUCTION_ALGORITHMS(int16_t, int16, and, &)
    REDUCTION_ALGORITHMS(uint32_t, uint32, and, &)
    REDUCTION_ALGORITHMS(int32_t, int32, and, &)
    REDUCTION_ALGORITHMS(uint64_t, uint64, and, &)
    REDUCTION_ALGORITHMS(int64_t, int64, and, &)
    REDUCTION_ALGORITHMS(size_t, size, and, &)

    /* Binary OR */
    REDUCTION_ALGORITHMS(unsigned char, uchar, or, |)
    REDUCTION_ALGORITHMS(unsigned short, ushort, or, |)
    REDUCTION_ALGORITHMS(unsigned int, uint, or, |)
    REDUCTION_ALGORITHMS(unsigned long, ulong, or, |)
    REDUCTION_ALGORITHMS(unsigned long long, ulonglong, or, |)
    REDUCTION_ALGORITHMS(uint8_t, uint8, or, |)
    REDUCTION_ALGORITHMS(int8_t, int8, or, |)
    REDUCTION_ALGORITHMS(uint16_t, uint16, or, |)
    REDUCTION_ALGORITHMS(int16_t, int16, or, |)
    REDUCTION_ALGORITHMS(uint32_t, uint32, or, |)
    REDUCTION_ALGORITHMS(int32_t, int32, or, |)
    REDUCTION_ALGORITHMS(uint64_t, uint64, or, |)
    REDUCTION_ALGORITHMS(int64_t, int64, or, |)
    REDUCTION_ALGORITHMS(size_t, size, or, |)

    /* Binary XOR */
    REDUCTION_ALGORITHMS(unsigned char, uchar, xor, ^)
    REDUCTION_ALGORITHMS(unsigned short, ushort, xor, ^)
    REDUCTION_ALGORITHMS(unsigned int, uint, xor, ^)
    REDUCTION_ALGORITHMS(unsigned long, ulong, xor, ^)
    REDUCTION_ALGORITHMS(unsigned long long, ulonglong, xor, ^)
    REDUCTION_ALGORITHMS(uint8_t, uint8, xor, ^)
    REDUCTION_ALGORITHMS(int8_t, int8, xor, ^)
    REDUCTION_ALGORITHMS(uint16_t, uint16, xor, ^)
    REDUCTION_ALGORITHMS(int16_t, int16, xor, ^)
    REDUCTION_ALGORITHMS(uint32_t, uint32, xor, ^)
    REDUCTION_ALGORITHMS(int32_t, int32, xor, ^)
    REDUCTION_ALGORITHMS(uint64_t, uint64, xor, ^)
    REDUCTION_ALGORITHMS(int64_t, int64, xor, ^)
    REDUCTION_ALGORITHMS(size_t, size, xor, ^)

#undef REDUCTION_ALGORITHMS


#define XBGAS_REDUCTION(_type, _typename, _funcname, _op)                                                                                               \
/* Wrapper function - recursive doubling for small messages, rabenseifner for large messages */                                                         \
int xbrtime_##_typename##_##_funcname##_reduce(_type *dest, const _type *src, size_t nreduce)                                                           \
{                                                                                                                                                       \
    if((sizeof(_type)*nreduce) < LARGE_REDUCE_ALL)                                                                                                      \
    {                                                                                                                                                   \
        return xbrtime_##_typename##_funcname##_recursive_doubling(dest, src, nreduce);                                                                 \
    }                                                                                                                                                   \
    else                                                                                                                                                \
    {                                                                                                                                                   \
        return xbrtime_##_typename##_funcname##_rabenseifner(dest, src, nreduce);                                                                       \
    }                                                                                                                                                   \
}

    /* Sum */
    XBGAS_REDUCTION(float, float, sum, +)
    XBGAS_REDUCTION(double, double, sum, +)
    XBGAS_REDUCTION(char, char, sum, +)
    XBGAS_REDUCTION(unsigned char, uchar, sum, +)
    XBGAS_REDUCTION(signed char, schar, sum, +)
    XBGAS_REDUCTION(unsigned short, ushort, sum, +)
    XBGAS_REDUCTION(short, short, sum, +)
    XBGAS_REDUCTION(unsigned int, uint, sum, +)
    XBGAS_REDUCTION(int, int, sum, +)
    XBGAS_REDUCTION(unsigned long, ulong, sum, +)
    XBGAS_REDUCTION(long, long, sum, +)
    XBGAS_REDUCTION(unsigned long long, ulonglong, sum, +)
    XBGAS_REDUCTION(long long, longlong, sum, +)
    XBGAS_REDUCTION(uint8_t, uint8, sum, +)
    XBGAS_REDUCTION(int8_t, int8, sum, +)
    XBGAS_REDUCTION(uint16_t, uint16, sum, +)
    XBGAS_REDUCTION(int16_t, int16, sum, +)
    XBGAS_REDUCTION(uint32_t, uint32, sum, +)
    XBGAS_REDUCTION(int32_t, int32, sum, +)
    XBGAS_REDUCTION(uint64_t, uint64, sum, +)
    XBGAS_REDUCTION(int64_t, int64, sum, +)
    XBGAS_REDUCTION(size_t, size, sum, +)
    XBGAS_REDUCTION(ptrdiff_t, ptrdiff, sum, +)

    /* Product */
    XBGAS_REDUCTION(float, float, product, *)
    XBGAS_REDUCTION(double, double, product, *)
    XBGAS_REDUCTION(char, char, product, *)
    XBGAS_REDUCTION(unsigned char, uchar, product, *)
    XBGAS_REDUCTION(signed char, schar, product, *)
    XBGAS_REDUCTION(unsigned short, ushort, product, *)
    XBGAS_REDUCTION(short, short, product, *)
    XBGAS_REDUCTION(unsigned int, uint, product, *)
    XBGAS_REDUCTION(int, int, product, *)
    XBGAS_REDUCTION(unsigned long, ulong, product, *)
    XBGAS_REDUCTION(long, long, product, *)
    XBGAS_REDUCTION(unsigned long long, ulonglong, product, *)
    XBGAS_REDUCTION(long long, longlong, product, *)
    XBGAS_REDUCTION(uint8_t, uint8, product, *)
    XBGAS_REDUCTION(int8_t, int8, product, *)
    XBGAS_REDUCTION(uint16_t, uint16, product, *)
    XBGAS_REDUCTION(int16_t, int16, product, *)
    XBGAS_REDUCTION(uint32_t, uint32, product, *)
    XBGAS_REDUCTION(int32_t, int32, product, *)
    XBGAS_REDUCTION(uint64_t, uint64, product, *)
    XBGAS_REDUCTION(int64_t, int64, product, *)
    XBGAS_REDUCTION(size_t, size, product, *)
    XBGAS_REDUCTION(ptrdiff_t, ptrdiff, product, *)

    /* Binary AND */
    XBGAS_REDUCTION(unsigned char, uchar, and, &)
    XBGAS_REDUCTION(unsigned short, ushort, and, &)
    XBGAS_REDUCTION(unsigned int, uint, and, &)
    XBGAS_REDUCTION(unsigned long, ulong, and, &)
    XBGAS_REDUCTION(unsigned long long, ulonglong, and, &)
    XBGAS_REDUCTION(uint8_t, uint8, and, &)
    XBGAS_REDUCTION(int8_t, int8, and, &)
    XBGAS_REDUCTION(uint16_t, uint16, and, &)
    XBGAS_REDUCTION(int16_t, int16, and, &)
    XBGAS_REDUCTION(uint32_t, uint32, and, &)
    XBGAS_REDUCTION(int32_t, int32, and, &)
    XBGAS_REDUCTION(uint64_t, uint64, and, &)
    XBGAS_REDUCTION(int64_t, int64, and, &)
    XBGAS_REDUCTION(size_t, size, and, &)

    /* Binary OR */
    XBGAS_REDUCTION(unsigned char, uchar, or, |)
    XBGAS_REDUCTION(unsigned short, ushort, or, |)
    XBGAS_REDUCTION(unsigned int, uint, or, |)
    XBGAS_REDUCTION(unsigned long, ulong, or, |)
    XBGAS_REDUCTION(unsigned long long, ulonglong, or, |)
    XBGAS_REDUCTION(uint8_t, uint8, or, |)
    XBGAS_REDUCTION(int8_t, int8, or, |)
    XBGAS_REDUCTION(uint16_t, uint16, or, |)
    XBGAS_REDUCTION(int16_t, int16, or, |)
    XBGAS_REDUCTION(uint32_t, uint32, or, |)
    XBGAS_REDUCTION(int32_t, int32, or, |)
    XBGAS_REDUCTION(uint64_t, uint64, or, |)
    XBGAS_REDUCTION(int64_t, int64, or, |)
    XBGAS_REDUCTION(size_t, size, or, |)

    /* Binary XOR */
    XBGAS_REDUCTION(unsigned char, uchar, xor, ^)
    XBGAS_REDUCTION(unsigned short, ushort, xor, ^)
    XBGAS_REDUCTION(unsigned int, uint, xor, ^)
    XBGAS_REDUCTION(unsigned long, ulong, xor, ^)
    XBGAS_REDUCTION(unsigned long long, ulonglong, xor, ^)
    XBGAS_REDUCTION(uint8_t, uint8, xor, ^)
    XBGAS_REDUCTION(int8_t, int8, xor, ^)
    XBGAS_REDUCTION(uint16_t, uint16, xor, ^)
    XBGAS_REDUCTION(int16_t, int16, xor, ^)
    XBGAS_REDUCTION(uint32_t, uint32, xor, ^)
    XBGAS_REDUCTION(int32_t, int32, xor, ^)
    XBGAS_REDUCTION(uint64_t, uint64, xor, ^)
    XBGAS_REDUCTION(int64_t, int64, xor, ^)
    XBGAS_REDUCTION(size_t, size, xor, ^)

#undef XBGAS_REDUCTION

#define REDUCTION_ALGORITHMS_MM(_type, _typename, _funcname, _op)                                                                                       \
int xbrtime_##_typename##_funcname##_recursive_doubling(_type *dest, const _type *src, size_t nreduce)                                                  \
{                                                                                                                                                       \
    int i, j, numpes, my_rpe, my_vpe, r_partner, numpes_log_floor, p_prime, remainder;                                                                  \
    numpes = xbrtime_num_pes();                                                                                                                         \
    my_rpe = xbrtime_mype();                                                                                                                            \
    my_vpe = my_rpe;                                                                                                                                    \
    numpes_log_floor = (int) (log(numpes)/log(2));                                                                                                      \
    p_prime = 1 << numpes_log_floor;                                                                                                                    \
    remainder = numpes - p_prime;                                                                                                                       \
    _type *accumulate = (_type*) xbrtime_malloc(sizeof(_type) * nreduce);                                                                               \
    _type *temp = (_type*) xbrtime_malloc(sizeof(_type) * nreduce);                                                                                     \
                                                                                                                                                        \
    /* Load reduction values into accumulate buffer */                                                                                                  \
    for(i = 0; i < nreduce; i++)                                                                                                                        \
    {                                                                                                                                                   \
        accumulate[i] = src[i];                                                                                                                         \
    }                                                                                                                                                   \
                                                                                                                                                        \
    /* Ensure buffer is ready */                                                                                                                        \
    xbrtime_barrier_all();                                                                                                                              \
                                                                                                                                                        \
    /* Stage 1 (only if NumPEs is not a power of two) */                                                                                                \
    if(numpes_log_floor != (log(numpes)/log(2)))                                                                                                        \
    {                                                                                                                                                   \
        /* First 2r ranks */                                                                                                                            \
        if(my_rpe < 2*remainder)                                                                                                                        \
        {                                                                                                                                               \
            /* Even ranks */                                                                                                                            \
            if(my_rpe % 2 == 0)                                                                                                                         \
            {                                                                                                                                           \
                /* Get values from my_rpe + 1 */                                                                                                        \
                xbrtime_##_typename##_get(temp, accumulate, nreduce, my_rpe + 1);                                                                       \
                                                                                                                                                        \
                /* Perform reduction op */                                                                                                              \
                for(j = 0; j < nreduce; j++)                                                                                                            \
                {                                                                                                                                       \
                    accumulate[j] = _op(accumulate[j], temp[j]);                                                                                        \
                }                                                                                                                                       \
                                                                                                                                                        \
                /* Assign new vpe ranks */                                                                                                              \
                my_vpe = my_rpe/2;                                                                                                                      \
            }                                                                                                                                           \
            /* Odd ranks */                                                                                                                             \
            else                                                                                                                                        \
            {                                                                                                                                           \
                /* Assign new vpe ranks */                                                                                                              \
                my_vpe = -1;                                                                                                                            \
            }                                                                                                                                           \
        }                                                                                                                                               \
        else                                                                                                                                            \
        {                                                                                                                                               \
            /* Assign new vpe ranks */                                                                                                                  \
            my_vpe = my_rpe - remainder;                                                                                                                \
        }                                                                                                                                               \
        xbrtime_barrier_all();                                                                                                                          \
    }                                                                                                                                                   \
                                                                                                                                                        \
    /* Stage 2 - Recursive Doubling */                                                                                                                  \
    int pe_stride = 1;                                                                                                                                  \
    for(i = 0; i < numpes_log_floor; i++)                                                                                                               \
    {                                                                                                                                                   \
        if(my_vpe != -1)                                                                                                                                \
        {                                                                                                                                               \
            if((my_vpe & ( 1 << i)) == 0)                                                                                                               \
            {                                                                                                                                           \
                /* Get from my_vpe + stride */                                                                                                          \
                r_partner = ((my_vpe+pe_stride) < remainder ? (my_vpe+pe_stride)*2 : (my_vpe+pe_stride)+remainder);                                     \
            }                                                                                                                                           \
            else                                                                                                                                        \
            {                                                                                                                                           \
                /* Get from my_vpe - stride */                                                                                                          \
                r_partner = (((my_vpe-pe_stride+p_prime)%p_prime) < remainder ? ((my_vpe-pe_stride+p_prime)%p_prime)*2 :                                \
                            ((my_vpe-pe_stride+p_prime)%p_prime)+remainder);                                                                            \
            }                                                                                                                                           \
                                                                                                                                                        \
            xbrtime_##_typename##_get(temp, accumulate, nreduce, r_partner);                                                                            \
        }                                                                                                                                               \
        /* Ensure get is complete */                                                                                                                    \
        xbrtime_barrier_all();                                                                                                                          \
                                                                                                                                                        \
        /* Perform reduction op */                                                                                                                      \
        if(my_vpe != -1)                                                                                                                                \
        {                                                                                                                                               \
            for(j = 0; j < nreduce; j++)                                                                                                                \
            {                                                                                                                                           \
                accumulate[j] = _op(accumulate[j], temp[j]);                                                                                            \
            }                                                                                                                                           \
        }                                                                                                                                               \
        pe_stride <<= 1;                                                                                                                                \
        xbrtime_barrier_all();                                                                                                                          \
    }                                                                                                                                                   \
                                                                                                                                                        \
    /* Put all reduced values to remainder PEs if not a power of two */                                                                                 \
    if(numpes_log_floor != (log(numpes)/log(2)))                                                                                                        \
    {                                                                                                                                                   \
        /* First r even rpe ranks*/                                                                                                                     \
        if((my_rpe < 2*remainder) && (my_rpe % 2 == 0))                                                                                                 \
        {                                                                                                                                               \
            xbrtime_##_typename##_put(accumulate, accumulate, nreduce, my_rpe + 1);                                                                     \
        }                                                                                                                                               \
        xbrtime_barrier_all();                                                                                                                          \
    }                                                                                                                                                   \
                                                                                                                                                        \
    /* Copy from buffer to dest with stride */                                                                                                          \
    for(i = 0; i < nreduce; i++)                                                                                                                        \
    {                                                                                                                                                   \
        dest[i] = accumulate[i];                                                                                                                        \
    }                                                                                                                                                   \
                                                                                                                                                        \
    xbrtime_free(accumulate);                                                                                                                           \
    xbrtime_free(temp);                                                                                                                                 \
    return 0;                                                                                                                                           \
}                                                                                                                                                       \
                                                                                                                                                        \
int xbrtime_##_typename##_funcname##_rabenseifner(_type *dest, const _type *src, size_t nreduce)                                                        \
{                                                                                                                                                       \
    int i, j, numpes, my_rpe, my_vpe, r_partner, numpes_log_floor, p_prime, remainder, counter;                                                         \
    numpes = xbrtime_num_pes();                                                                                                                         \
    my_rpe = xbrtime_mype();                                                                                                                            \
    my_vpe = my_rpe;                                                                                                                                    \
    numpes_log_floor = (int) (log(numpes)/log(2));                                                                                                      \
    p_prime = 1 << numpes_log_floor;                                                                                                                    \
    remainder = numpes - p_prime;                                                                                                                       \
    _type *accumulate = (_type*) xbrtime_malloc(sizeof(_type) * nreduce);                                                                               \
    _type *temp = (_type*) xbrtime_malloc(sizeof(_type) * nreduce);                                                                                     \
                                                                                                                                                        \
    /* Load reduction values into accumulate buffer and remove stride */                                                                                \
    for(i = 0; i < nreduce; i++)                                                                                                                        \
    {                                                                                                                                                   \
        accumulate[i] = src[i];                                                                                                                         \
    }                                                                                                                                                   \
                                                                                                                                                        \
    /* Divide buffers into p_prime partitions */                                                                                                        \
    counter = 0;                                                                                                                                        \
    int partition_sizes[p_prime], partition_disp[p_prime];                                                                                              \
    for(i = 0; i < p_prime; i++)                                                                                                                        \
    {                                                                                                                                                   \
        partition_sizes[i] = ( (i == p_prime-1) ?                                                                                                       \
                             (((int)(nreduce/p_prime)) + (nreduce%p_prime)) :                                                                           \
                             ((int)(nreduce/p_prime)) );                                                                                                \
        partition_disp[i] = counter;                                                                                                                    \
        counter += partition_sizes[i];                                                                                                                  \
    }                                                                                                                                                   \
                                                                                                                                                        \
    /* Ensure buffer is ready */                                                                                                                        \
    xbrtime_barrier_all();                                                                                                                              \
                                                                                                                                                        \
    int num_exchange = p_prime/2;                                                                                                                       \
    int msg_size = 0;                                                                                                                                   \
                                                                                                                                                        \
    /* Stage 1 - ReduceScatter (only if NumPEs is not a power of two) */                                                                                \
    if(numpes_log_floor != (log(numpes)/log(2)))                                                                                                        \
    {                                                                                                                                                   \
        /* First 2r ranks */                                                                                                                            \
        if(my_rpe < 2*remainder)                                                                                                                        \
        {                                                                                                                                               \
            /* Even ranks */                                                                                                                            \
            if(my_rpe % 2 == 0)                                                                                                                         \
            {                                                                                                                                           \
                /* Calculate and get first half of values from my_rpe + 1 */                                                                            \
                for(j = 0; j < num_exchange; j++)                                                                                                       \
                {                                                                                                                                       \
                    msg_size += partition_sizes[j];                                                                                                     \
                }                                                                                                                                       \
                                                                                                                                                        \
                xbrtime_##_typename##_get(temp, accumulate, msg_size, my_rpe + 1);                                                                      \
                                                                                                                                                        \
                /* Perform reduction op */                                                                                                              \
                for(j = 0; j < msg_size; j++)                                                                                                           \
                {                                                                                                                                       \
                    accumulate[j] = _op(accumulate[j], temp[j]);                                                                                        \
                }                                                                                                                                       \
                                                                                                                                                        \
                /* Assign new vpe ranks */                                                                                                              \
                my_vpe = my_rpe/2;                                                                                                                      \
            }                                                                                                                                           \
            /* Odd ranks */                                                                                                                             \
            else                                                                                                                                        \
            {                                                                                                                                           \
                /* Calculate and get second half of values from my_rpe - 1 */                                                                           \
                for(j = num_exchange; j < p_prime; j++)                                                                                                 \
                {                                                                                                                                       \
                    msg_size += partition_sizes[j];                                                                                                     \
                }                                                                                                                                       \
                                                                                                                                                        \
                xbrtime_##_typename##_get(&(temp[(partition_disp[num_exchange])]), &(accumulate[(partition_disp[num_exchange])]),                       \
                                            msg_size, my_rpe - 1);                                                                                      \
                                                                                                                                                        \
                /* Perform reduction op */                                                                                                              \
                for(j = 0; j < msg_size; j++)                                                                                                           \
                {                                                                                                                                       \
                    accumulate[(partition_disp[num_exchange])+j] = _op(accumulate[(partition_disp[num_exchange])+j],                                    \
                                                                        temp[(partition_disp[num_exchange])+j]);                                        \
                }                                                                                                                                       \
                                                                                                                                                        \
                /* Put calculated second half values back to even partner */                                                                            \
                xbrtime_##_typename##_put(&(accumulate[(partition_disp[num_exchange])]), &(accumulate[(partition_disp[num_exchange])]),                 \
                                            msg_size, my_rpe - 1);                                                                                      \
                                                                                                                                                        \
                /* Assign new vpe ranks */                                                                                                              \
                my_vpe = -1;                                                                                                                            \
            }                                                                                                                                           \
        }                                                                                                                                               \
        else                                                                                                                                            \
        {                                                                                                                                               \
            /* Assign new vpe ranks */                                                                                                                  \
            my_vpe = my_rpe - remainder;                                                                                                                \
        }                                                                                                                                               \
        xbrtime_barrier_all();                                                                                                                          \
    }                                                                                                                                                   \
                                                                                                                                                        \
    /* Stage 2 - ReduceScatter Recursive Doubling/Halving */                                                                                            \
    int pe_stride = 1;                                                                                                                                  \
    int offset = 0;                                                                                                                                     \
    for(i = 0; i < numpes_log_floor; i++)                                                                                                               \
    {                                                                                                                                                   \
        msg_size = 0;                                                                                                                                   \
        if(my_vpe != -1)                                                                                                                                \
        {                                                                                                                                               \
            /* PEs perform get and reduction of first buffer half */                                                                                    \
            if((my_vpe & ( 1 << i)) == 0)                                                                                                               \
            {                                                                                                                                           \
                r_partner = ((my_vpe+pe_stride) < remainder ? (my_vpe+pe_stride)*2 : (my_vpe+pe_stride)+remainder);                                     \
                                                                                                                                                        \
                /* Calculate msg_size */                                                                                                                \
                for(j = 0; j < num_exchange; j++)                                                                                                       \
                {                                                                                                                                       \
                    msg_size += partition_sizes[offset+j];                                                                                              \
                }                                                                                                                                       \
                                                                                                                                                        \
                xbrtime_##_typename##_get(&(temp[(partition_disp[offset])]), &(accumulate[(partition_disp[offset])]), msg_size, r_partner);             \
                                                                                                                                                        \
                /* Perform reduction op */                                                                                                              \
                for(j = 0; j < msg_size; j++)                                                                                                           \
                {                                                                                                                                       \
                    accumulate[(partition_disp[offset]+j)] = _op(accumulate[(partition_disp[offset])+j], temp[(partition_disp[offset])+j]);             \
                }                                                                                                                                       \
            }                                                                                                                                           \
            /* PEs perform get and reduction of second buffer half */                                                                                   \
            else                                                                                                                                        \
            {                                                                                                                                           \
                r_partner = (((my_vpe-pe_stride+p_prime)%p_prime) < remainder ? ((my_vpe-pe_stride+p_prime)%p_prime)*2 :                                \
                            ((my_vpe-pe_stride+p_prime)%p_prime)+remainder);                                                                            \
                                                                                                                                                        \
                /* Calculate msg_size */                                                                                                                \
                for(j = 0; j < num_exchange; j++)                                                                                                       \
                {                                                                                                                                       \
                    msg_size += partition_sizes[offset+num_exchange+j];                                                                                 \
                }                                                                                                                                       \
                                                                                                                                                        \
                xbrtime_##_typename##_get(&(temp[(partition_disp[offset+num_exchange])]), &(accumulate[(partition_disp[offset+num_exchange])]),         \
                                            msg_size, r_partner);                                                                                       \
                                                                                                                                                        \
                /* Perform reduction op */                                                                                                              \
                for(j = 0; j < msg_size; j++)                                                                                                           \
                {                                                                                                                                       \
                    accumulate[(partition_disp[offset+num_exchange])+j] = _op(accumulate[(partition_disp[offset+num_exchange])+j],                      \
                                                                            temp[(partition_disp[offset+num_exchange])+j]);                             \
                }                                                                                                                                       \
                                                                                                                                                        \
                /* Increase offset for these PEs*/                                                                                                      \
                offset += num_exchange;                                                                                                                 \
            }                                                                                                                                           \
        }                                                                                                                                               \
        num_exchange >>= 1;                                                                                                                             \
        pe_stride <<= 1;                                                                                                                                \
        xbrtime_barrier_all();                                                                                                                          \
    }                                                                                                                                                   \
                                                                                                                                                        \
    /* Stage 3 - GatherAll */                                                                                                                           \
    pe_stride = (1 << (numpes_log_floor-1));                                                                                                            \
    num_exchange = 1;                                                                                                                                   \
    for(i = numpes_log_floor - 1; i >= 0; i--)                                                                                                          \
    {                                                                                                                                                   \
        msg_size = 0;                                                                                                                                   \
        if(my_vpe != -1)                                                                                                                                \
        {                                                                                                                                               \
            /* PEs perform put */                                                                                                                       \
            if((my_vpe & ( 1 << i)) == 0)                                                                                                               \
            {                                                                                                                                           \
                r_partner = ((my_vpe+pe_stride) < remainder ? (my_vpe+pe_stride)*2 : (my_vpe+pe_stride)+remainder);                                     \
                                                                                                                                                        \
                /* Calculate msg_size */                                                                                                                \
                for(j = 0; j < num_exchange; j++)                                                                                                       \
                {                                                                                                                                       \
                    msg_size += partition_sizes[offset+j];                                                                                              \
                }                                                                                                                                       \
                                                                                                                                                        \
                xbrtime_##_typename##_put(&(accumulate[(partition_disp[offset])]), &(accumulate[(partition_disp[offset])]), msg_size, r_partner);       \
            }                                                                                                                                           \
            /* PEs perform put*/                                                                                                                        \
            else                                                                                                                                        \
            {                                                                                                                                           \
                r_partner = (((my_vpe-pe_stride+p_prime)%p_prime) < remainder ? ((my_vpe-pe_stride+p_prime)%p_prime)*2 :                                \
                            ((my_vpe-pe_stride+p_prime)%p_prime)+remainder);                                                                            \
                                                                                                                                                        \
                /* Decrease offset for these PEs*/                                                                                                      \
                offset -= num_exchange;                                                                                                                 \
                                                                                                                                                        \
                /* Calculate msg_size */                                                                                                                \
                for(j = 0; j < num_exchange; j++)                                                                                                       \
                {                                                                                                                                       \
                    msg_size += partition_sizes[offset+num_exchange+j];                                                                                 \
                }                                                                                                                                       \
                                                                                                                                                        \
                xbrtime_##_typename##_put(&(accumulate[(partition_disp[offset+num_exchange])]), &(accumulate[(partition_disp[offset+num_exchange])]),   \
                                          msg_size, r_partner);                                                                                         \
            }                                                                                                                                           \
        }                                                                                                                                               \
        num_exchange <<= 1;                                                                                                                             \
        pe_stride >>= 1;                                                                                                                                \
        xbrtime_barrier_all();                                                                                                                          \
    }                                                                                                                                                   \
                                                                                                                                                        \
    /* Put all reduced values to remainder PEs if not a power of two */                                                                                 \
    if(numpes_log_floor != (log(numpes)/log(2)))                                                                                                        \
    {                                                                                                                                                   \
        /* First r even rpe ranks*/                                                                                                                     \
        if((my_rpe < 2*remainder) && (my_rpe % 2 == 0))                                                                                                 \
        {                                                                                                                                               \
            xbrtime_##_typename##_put(accumulate, accumulate, nreduce, my_rpe + 1);                                                                     \
        }                                                                                                                                               \
        xbrtime_barrier_all();                                                                                                                          \
    }                                                                                                                                                   \
                                                                                                                                                        \
    /* Copy from buffer to dest with stride */                                                                                                          \
    for(i = 0; i < nreduce; i++)                                                                                                                        \
    {                                                                                                                                                   \
        dest[i] = accumulate[i];                                                                                                                        \
    }                                                                                                                                                   \
                                                                                                                                                        \
    xbrtime_free(accumulate);                                                                                                                           \
    xbrtime_free(temp);                                                                                                                                 \
    return 0;                                                                                                                                           \
}                                                                                                                                                       \
/* Max */
    REDUCTION_ALGORITHMS_MM(float, float, max, MAX)
    REDUCTION_ALGORITHMS_MM(double, double, max, MAX)
    REDUCTION_ALGORITHMS_MM(char, char, max, MAX)
    REDUCTION_ALGORITHMS_MM(unsigned char, uchar, max, MAX)
    REDUCTION_ALGORITHMS_MM(signed char, schar, max, MAX)
    REDUCTION_ALGORITHMS_MM(unsigned short, ushort, max, MAX)
    REDUCTION_ALGORITHMS_MM(short, short, max, MAX)
    REDUCTION_ALGORITHMS_MM(unsigned int, uint, max, MAX)
    REDUCTION_ALGORITHMS_MM(int, int, max, MAX)
    REDUCTION_ALGORITHMS_MM(unsigned long, ulong, max, MAX)
    REDUCTION_ALGORITHMS_MM(long, long, max, MAX)
    REDUCTION_ALGORITHMS_MM(unsigned long long, ulonglong, max, MAX)
    REDUCTION_ALGORITHMS_MM(long long, longlong, max, MAX)
    REDUCTION_ALGORITHMS_MM(uint8_t, uint8, max, MAX)
    REDUCTION_ALGORITHMS_MM(int8_t, int8, max, MAX)
    REDUCTION_ALGORITHMS_MM(uint16_t, uint16, max, MAX)
    REDUCTION_ALGORITHMS_MM(int16_t, int16, max, MAX)
    REDUCTION_ALGORITHMS_MM(uint32_t, uint32, max, MAX)
    REDUCTION_ALGORITHMS_MM(int32_t, int32, max, MAX)
    REDUCTION_ALGORITHMS_MM(uint64_t, uint64, max, MAX)
    REDUCTION_ALGORITHMS_MM(int64_t, int64, max, MAX)
    REDUCTION_ALGORITHMS_MM(size_t, size, max, MAX)
    REDUCTION_ALGORITHMS_MM(ptrdiff_t, ptrdiff, max, MAX)

    /* Min */
    REDUCTION_ALGORITHMS_MM(float, float, min, MIN)
    REDUCTION_ALGORITHMS_MM(double, double, min, MIN)
    REDUCTION_ALGORITHMS_MM(char, char, min, MIN)
    REDUCTION_ALGORITHMS_MM(unsigned char, uchar, min, MIN)
    REDUCTION_ALGORITHMS_MM(signed char, schar, min, MIN)
    REDUCTION_ALGORITHMS_MM(unsigned short, ushort, min, MIN)
    REDUCTION_ALGORITHMS_MM(short, short, min, MIN)
    REDUCTION_ALGORITHMS_MM(unsigned int, uint, min, MIN)
    REDUCTION_ALGORITHMS_MM(int, int, min, MIN)
    REDUCTION_ALGORITHMS_MM(unsigned long, ulong, min, MIN)
    REDUCTION_ALGORITHMS_MM(long, long, min, MIN)
    REDUCTION_ALGORITHMS_MM(unsigned long long, ulonglong, min, MIN)
    REDUCTION_ALGORITHMS_MM(long long, longlong, min, MIN)
    REDUCTION_ALGORITHMS_MM(uint8_t, uint8, min, MIN)
    REDUCTION_ALGORITHMS_MM(int8_t, int8, min, MIN)
    REDUCTION_ALGORITHMS_MM(uint16_t, uint16, min, MIN)
    REDUCTION_ALGORITHMS_MM(int16_t, int16, min, MIN)
    REDUCTION_ALGORITHMS_MM(uint32_t, uint32, min, MIN)
    REDUCTION_ALGORITHMS_MM(int32_t, int32, min, MIN)
    REDUCTION_ALGORITHMS_MM(uint64_t, uint64, min, MIN)
    REDUCTION_ALGORITHMS_MM(int64_t, int64, min, MIN)
    REDUCTION_ALGORITHMS_MM(size_t, size, min, MIN)
    REDUCTION_ALGORITHMS_MM(ptrdiff_t, ptrdiff, min, MIN)

#undef REDUCTION_ALGORITHMS_MM

#define XBGAS_REDUCTION_MM(_type, _typename, _funcname, _op)                                                                                            \
/* Wrapper function - recursive doubling for small messages, rabenseifner for large messages */                                                         \
int xbrtime_##_typename##_##_funcname##_reduce(_type *dest, const _type *src, size_t nreduce)                                                           \
{                                                                                                                                                       \
    if((sizeof(_type)*nreduce) < LARGE_REDUCE_ALL)                                                                                                      \
    {                                                                                                                                                   \
        return xbrtime_##_typename##_funcname##_recursive_doubling(dest, src, nreduce);                                                                 \
    }                                                                                                                                                   \
    else                                                                                                                                                \
    {                                                                                                                                                   \
        return xbrtime_##_typename##_funcname##_rabenseifner(dest, src, nreduce);                                                                       \
    }                                                                                                                                                   \
}

    /* Max */
    XBGAS_REDUCTION_MM(float, float, max, MAX)
    XBGAS_REDUCTION_MM(double, double, max, MAX)
    XBGAS_REDUCTION_MM(char, char, max, MAX)
    XBGAS_REDUCTION_MM(unsigned char, uchar, max, MAX)
    XBGAS_REDUCTION_MM(signed char, schar, max, MAX)
    XBGAS_REDUCTION_MM(unsigned short, ushort, max, MAX)
    XBGAS_REDUCTION_MM(short, short, max, MAX)
    XBGAS_REDUCTION_MM(unsigned int, uint, max, MAX)
    XBGAS_REDUCTION_MM(int, int, max, MAX)
    XBGAS_REDUCTION_MM(unsigned long, ulong, max, MAX)
    XBGAS_REDUCTION_MM(long, long, max, MAX)
    XBGAS_REDUCTION_MM(unsigned long long, ulonglong, max, MAX)
    XBGAS_REDUCTION_MM(long long, longlong, max, MAX)
    XBGAS_REDUCTION_MM(uint8_t, uint8, max, MAX)
    XBGAS_REDUCTION_MM(int8_t, int8, max, MAX)
    XBGAS_REDUCTION_MM(uint16_t, uint16, max, MAX)
    XBGAS_REDUCTION_MM(int16_t, int16, max, MAX)
    XBGAS_REDUCTION_MM(uint32_t, uint32, max, MAX)
    XBGAS_REDUCTION_MM(int32_t, int32, max, MAX)
    XBGAS_REDUCTION_MM(uint64_t, uint64, max, MAX)
    XBGAS_REDUCTION_MM(int64_t, int64, max, MAX)
    XBGAS_REDUCTION_MM(size_t, size, max, MAX)
    XBGAS_REDUCTION_MM(ptrdiff_t, ptrdiff, max, MAX)

    /* Min */
    XBGAS_REDUCTION_MM(float, float, min, MIN)
    XBGAS_REDUCTION_MM(double, double, min, MIN)
    XBGAS_REDUCTION_MM(char, char, min, MIN)
    XBGAS_REDUCTION_MM(unsigned char, uchar, min, MIN)
    XBGAS_REDUCTION_MM(signed char, schar, min, MIN)
    XBGAS_REDUCTION_MM(unsigned short, ushort, min, MIN)
    XBGAS_REDUCTION_MM(short, short, min, MIN)
    XBGAS_REDUCTION_MM(unsigned int, uint, min, MIN)
    XBGAS_REDUCTION_MM(int, int, min, MIN)
    XBGAS_REDUCTION_MM(unsigned long, ulong, min, MIN)
    XBGAS_REDUCTION_MM(long, long, min, MIN)
    XBGAS_REDUCTION_MM(unsigned long long, ulonglong, min, MIN)
    XBGAS_REDUCTION_MM(long long, longlong, min, MIN)
    XBGAS_REDUCTION_MM(uint8_t, uint8, min, MIN)
    XBGAS_REDUCTION_MM(int8_t, int8, min, MIN)
    XBGAS_REDUCTION_MM(uint16_t, uint16, min, MIN)
    XBGAS_REDUCTION_MM(int16_t, int16, min, MIN)
    XBGAS_REDUCTION_MM(uint32_t, uint32, min, MIN)
    XBGAS_REDUCTION_MM(int32_t, int32, min, MIN)
    XBGAS_REDUCTION_MM(uint64_t, uint64, min, MIN)
    XBGAS_REDUCTION_MM(int64_t, int64, min, MIN)
    XBGAS_REDUCTION_MM(size_t, size, min, MIN)
    XBGAS_REDUCTION_MM(ptrdiff_t, ptrdiff, min, MIN)

#undef XBGAS_REDUCTION_MM

#undef MAX
#undef MIN

/* EOF */