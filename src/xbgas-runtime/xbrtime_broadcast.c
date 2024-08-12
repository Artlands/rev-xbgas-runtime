/*
 * _XBRTIME_BROADCAST_C_
 *
 * Copyright (C) 2017-2019  Tactical Computing Laboratories, LLC
 * All Rights Reserved
 * contact@tactcomplabs.com
 *
 * This file is a part of the XBGAS-RUNTIME package.  For license
 * information, see the LICENSE file in the top level directory
 * of the distribution.
 *
 */

 #include "xbrtime.h"

 #define XBGAS_BROADCAST(_type, _typename)                                                                                  \
 void xbrtime_##_typename##_broadcast_tree(_type *dest, const _type *src, size_t nelems, int stride, int root)              \
 {                                                                                                                          \
     int i, numpes, my_rpe, my_vpe, numpes_log, mask, two_i, r_partner, v_partner;                                          \
     numpes = xbrtime_num_pes();                                                                                            \
     my_rpe = xbrtime_mype();                                                                                               \
     my_vpe = ((my_rpe >= root) ? (my_rpe - root) : (my_rpe + numpes - root));                                              \
     _type *temp = (_type*) xbrtime_malloc(sizeof(_type) * nelems);							    \
     numpes_log = (int) ceil((log(numpes)/log(2)));  /* Number of commmuication stages */                                   \
     mask = (int) (pow(2,numpes_log) - 1);                                                                                  \
															    \
     /* Root load values into buffer without stride */									    \
     if(my_rpe == root)													    \
     {															    \
	 for(i = 0; i < nelems; i++)											    \
	 {														    \
	     temp[i] = src[i*stride];											    \
	 }														    \
     }															    \
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
                 xbrtime_##_typename##_put(temp, temp, nelems, 1, r_partner);                                               \
             }                                                                                                              \
         }                                                                                                                  \
         xbrtime_barrier();                                                                                                 \
          /*printf("subset after i = %d, myrpe=%d\n", i, my_rpe); */\
     }                                                                                                                      \
															    \
     /* Migrate from buffer to dest with stride */                                                                          \
     for(i = 0; i < nelems; i++)                                                                                            \
     {                                                                                                                      \
         dest[i*stride] = temp[i];                                                                                          \
     }                                                                                                                      \
     xbrtime_free(temp);                                                                                                    \
}                                                                                                                           \
                                                                                                                            \
 void xbrtime_##_typename##_broadcast_van_de_geijn(_type *dest, const _type *src, size_t nelems, int stride, int root)      \
 {                                                                                                                          \
     int i, numpes, my_rpe, counter;                                                                                        \
     numpes = xbrtime_num_pes();                                                                                            \
     my_rpe = xbrtime_mype();                                                                                               \
     _type *temp = (_type*) xbrtime_malloc(sizeof(_type) * nelems);                                                         \
     int pe_msg_sz[numpes], pe_disp[numpes];                                                                                \
                                                                                                                            \
     counter = 0;                                                                                                           \
     for(i = 0; i < numpes; i++)                                                                                            \
     {                                                                                                                      \
         pe_msg_sz[i] = ( (i == numpes-1) ? (((int)(nelems/numpes))+(nelems%numpes)) : ((int)(nelems/numpes)) );            \
         pe_disp[i] = counter;                                                                                              \
         counter += pe_msg_sz[i];                                                                                           \
     }                                                                                                                      \
                                                                                                                            \
     /* Root load values into buffer without stride */                                                                      \
     if(my_rpe == root)                                                                                                     \
     {                                                                                                                      \
         for(i = 0; i < nelems; i++)                                                                                        \
         {                                                                                                                  \
             temp[i] = src[i*stride];                                                                                       \
         }                                                                                                                  \
     }                                                                                                                      \
                                                                                                                            \
     /* Ensure buffer is ready */                                                                                           \
     xbrtime_barrier();                                                                                                     \
                                                                                                                            \
     /* Scatter data using binomial tree */                                                                                 \
     xbrtime_##_typename##_scatter_tree(&(temp[(pe_disp[my_rpe])]), temp, pe_msg_sz, pe_disp, nelems, root);                \
                                                                                                                            \
     /* Perform ring gather_all */                                                                                          \
     xbrtime_##_typename##_gather_all_ring(temp, &(temp[(pe_disp[my_rpe])]), pe_msg_sz, pe_disp, nelems);                   \
                                                                                                                            \
     /* Migrate from buffer to dest with stride */                                                                          \
     for(i = 0; i < nelems; i++)                                                                                            \
     {                                                                                                                      \
         dest[i*stride] = temp[i];                                                                                          \
     }                                                                                                                      \
     xbrtime_free(temp);                                                                                                    \
 }                                                                                                                          \
                                                                                                                            \
 /* Wrapper function - binomial tree for small messages, van de geijn for large messages */                                 \
 void xbrtime_##_typename##_broadcast(_type *dest, const _type *src, size_t nelems, int stride, int root)                   \
 {                                                                                                                          \
     if((sizeof(_type)*nelems) < LARGE_BROADCAST)                                                                           \
     {                                                                                                                      \
         xbrtime_##_typename##_broadcast_tree(dest, src, nelems, stride, root);                                             \
     }                                                                                                                      \
     else                                                                                                                   \
     {                                                                                                                      \
         xbrtime_##_typename##_broadcast_van_de_geijn(dest, src, nelems, stride, root);                                     \
     }                                                                                                                      \
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


#define XBGAS_BROADCAST_SUBSET(_type, _typename)                                                                                  \
void xbrtime_##_typename##_broadcast_subset_tree(_type *dest, const _type *src, size_t nelems, int stride, int root, const int *subset, size_t subset_size) \
{                                                                                                                          \
    int i, numpes, my_rpe, my_vpe, numpes_log, mask, two_i, r_partner, v_partner;                                          \
    numpes = subset_size;                                                                                                  \
    my_rpe = xbrtime_mype();                                                                                               \
                                                                                                                           \
    int subset_index = -1;                                                                                                  \
    int root_index = -1;                                                                                                 \
    for(i = 0; i < subset_size; i++) {                                                                                     \
        if(subset[i] == my_rpe) {                                                                                          \
            subset_index = i;                                                                                               \                
            if (my_rpe == root) {                                                                                           \
                root_index = i;                                                                                             \
            }                                                                                                               \
            break;                                                                                                         \
        }                                                                                                                  \
    }                                                                                                                      \
    if(subset_index == -1) {                \
        numpes_log = (int) ceil((log(numpes)/log(2)));  /* Number of communication stages */                               \
        for(i = numpes_log-1; i >= 0; i--)                                                                                 \
        {                                                                                                                      \
            /*printf("non subset before i = %d, myrpe=%d, subset_index=%d\n", i, my_rpe, subset_index); */ \
            xbrtime_barrier();                                                                                                 \
            /*printf("non subset after i = %d, myrpe=%d, subset_index=%d\n", i, my_rpe, subset_index); */ \
        }                                                                                                                      \
        return;         \
    }                                      \
                                                                                                                           \
    my_vpe = ((subset_index >= root_index) ? (subset_index - root_index) : (subset_index + numpes - root_index));                            \
    _type *temp = (_type*) xbrtime_malloc(sizeof(_type) * nelems);							    \
    numpes_log = (int) ceil((log(numpes)/log(2)));  /* Number of communication stages */                                   \
    mask = (int) (pow(2,numpes_log) - 1);                                                                                  \
    /* Root load values into buffer without stride */									    \
    if(subset[root_index] == my_rpe)													    \
    {															    \
        for(i = 0; i < nelems; i++)											    \
        {														    \
            temp[i] = src[i*stride];											    \
        }														    \
    }															    \
                                                                                                                            \
    /* Perform communication if PE active at stage i and has valid partner */                                              \
    for(i = numpes_log-1; i >= 0; i--)                                                                                     \
    {                                                                                                                      \
        two_i = (int) pow(2,i);                                                                                            \
        mask = mask ^ two_i;                                                                                               \
        if(((my_vpe & mask) == 0) && ((my_vpe & two_i) == 0))                                                              \
        {                                                                                                                  \
            v_partner = (my_vpe ^ two_i);                                                                                  \
            if(v_partner < numpes) {                                                                                       \
                r_partner = subset[(v_partner + root_index) % numpes];                                                           \
                if(my_vpe < v_partner)                                                                                     \
                {                                                                                                          \
                    xbrtime_##_typename##_put(temp, temp, nelems, 1, r_partner);                                           \
                }                                                                                                          \
            }                                                                                                              \
        }                                                                                                                  \
        /* printf("subset before i = %d, myrpe=%d, subset_index=%d\n", i, my_rpe, subset_index);  */ \
        xbrtime_barrier();                                                                                                 \
        /* printf("subset after i = %d, myrpe=%d, subset_index=%d\n", i, my_rpe, subset_index);  */ \
    }                                                                                                                      \
															    \
    /* Migrate from buffer to dest with stride */                                                                          \
    for(i = 0; i < nelems; i++)                                                                                            \
    {                                                                                                                      \
        dest[i*stride] = temp[i];                                                                                          \
    }                                                                                                                      \
    xbrtime_free(temp);                                                                                                    \
}

    XBGAS_BROADCAST_SUBSET(float, float)
    XBGAS_BROADCAST_SUBSET(double, double)
    XBGAS_BROADCAST_SUBSET(char, char)
    XBGAS_BROADCAST_SUBSET(unsigned char, uchar)
    XBGAS_BROADCAST_SUBSET(signed char, schar)
    XBGAS_BROADCAST_SUBSET(unsigned short, ushort)
    XBGAS_BROADCAST_SUBSET(short, short)
    XBGAS_BROADCAST_SUBSET(unsigned int, uint)
    XBGAS_BROADCAST_SUBSET(int, int)
    XBGAS_BROADCAST_SUBSET(unsigned long, ulong)
    XBGAS_BROADCAST_SUBSET(long, long)
    XBGAS_BROADCAST_SUBSET(unsigned long long, ulonglong)
    XBGAS_BROADCAST_SUBSET(long long, longlong)
    XBGAS_BROADCAST_SUBSET(uint8_t, uint8)
    XBGAS_BROADCAST_SUBSET(int8_t, int8)
    XBGAS_BROADCAST_SUBSET(uint16_t, uint16)
    XBGAS_BROADCAST_SUBSET(int16_t, int16)
    XBGAS_BROADCAST_SUBSET(uint32_t, uint32)
    XBGAS_BROADCAST_SUBSET(int32_t, int32)
    XBGAS_BROADCAST_SUBSET(uint64_t, uint64)
    XBGAS_BROADCAST_SUBSET(int64_t, int64)
    XBGAS_BROADCAST_SUBSET(size_t, size)
    XBGAS_BROADCAST_SUBSET(ptrdiff_t, ptrdiff)
//  XBGAS_BROADCAST_SUBSET(long double, longdouble)

#undef XBGAS_BROADCAST_SUBSET