/*
 * _XBRTIME_COLLECTIVES_H_
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

#ifndef _XBRTIME_COLLECTIVES_H_
#define _XBRTIME_COLLECTIVES_H_

/* Large message size thresholds (bytes) */
#define LARGE_BROADCAST             12288
#define LARGE_REDUCE                2048
#define LARGE_REDUCE_ALL            2048
#define LARGE_GATHER_ALL            81920

#ifdef __cplusplus
extern "C" {
#endif

/*! \fn int xbrtime_TYPENAME_broadcast( TYPE *dest, const TYPE *src, size_t nelems, int stride, int root )
    \brief Broadcasts one or more values of type TYPE from the root to all PEs
    \param dest is a pointer to the base shared address where broadcasted values are placed on each PE
    \param src is a pointer to the base shared address on root where values to be broadcast are located
    \param nelems is the number of elements to be broadcast to each PE
    \param root is the PE id of the root PE
    \return int zero on successful local completion; otherwise, nonzero.
*/
#define XBGAS_DECL_BROADCAST(_type, _typename)                                             \
int xbrtime_##_typename##_broadcast(_type *dest, const _type *src, size_t nelems, int root);

    XBGAS_DECL_BROADCAST(float, float)
    XBGAS_DECL_BROADCAST(double, double)
    XBGAS_DECL_BROADCAST(char, char)
    XBGAS_DECL_BROADCAST(unsigned char, uchar)
    XBGAS_DECL_BROADCAST(signed char, schar)
    XBGAS_DECL_BROADCAST(unsigned short, ushort)
    XBGAS_DECL_BROADCAST(short, short)
    XBGAS_DECL_BROADCAST(unsigned int, uint)
    XBGAS_DECL_BROADCAST(int, int)
    XBGAS_DECL_BROADCAST(unsigned long, ulong)
    XBGAS_DECL_BROADCAST(long, long)
    XBGAS_DECL_BROADCAST(unsigned long long, ulonglong)
    XBGAS_DECL_BROADCAST(long long, longlong)
    XBGAS_DECL_BROADCAST(uint8_t, uint8)
    XBGAS_DECL_BROADCAST(int8_t, int8)
    XBGAS_DECL_BROADCAST(uint16_t, uint16)
    XBGAS_DECL_BROADCAST(int16_t, int16)
    XBGAS_DECL_BROADCAST(uint32_t, uint32)
    XBGAS_DECL_BROADCAST(int32_t, int32)
    XBGAS_DECL_BROADCAST(uint64_t, uint64)
    XBGAS_DECL_BROADCAST(int64_t, int64)
    XBGAS_DECL_BROADCAST(size_t, size)
    XBGAS_DECL_BROADCAST(ptrdiff_t, ptrdiff)

#undef XBGAS_DECL_BROADCAST

/*! \fn int xbrtime_TYPENAME_collect/fcollect( TYPE *dest, const TYPE *src, size_t nelems )
    \brief Concatenates blocks of data from multiple PEs to an array in every PE participating in the collective routine. 
    The fcollect routines require that nelems be the same value in all participating PEs, while the collect routines allow nelems to vary from PE to PE.
    Currently, fcollect and collect use the same algorithm and do not support varying nelems.
    \param dest is the symmetric address of an array large enough to accept the concatenation of the source arrays on all participating PEs
    \param src is the symmetric address of the source data object.
    \param nelems is the number of elements in source array
    \return int zero on successful local completion; otherwise, nonzero.
*/

#define XBGAS_DECL_COLLECT(_type, _typename)                                        \
int xbrtime_##_typename##_collect(_type *dest, const _type *src, size_t nelems);    \
int xbrtime_##_typename##_fcollect(_type *dest, const _type *src, size_t nelems);

    XBGAS_DECL_COLLECT(float, float)
    XBGAS_DECL_COLLECT(double, double)
    XBGAS_DECL_COLLECT(char, char)
    XBGAS_DECL_COLLECT(unsigned char, uchar)
    XBGAS_DECL_COLLECT(signed char, schar)
    XBGAS_DECL_COLLECT(unsigned short, ushort)
    XBGAS_DECL_COLLECT(short, short)
    XBGAS_DECL_COLLECT(unsigned int, uint)
    XBGAS_DECL_COLLECT(int, int)
    XBGAS_DECL_COLLECT(unsigned long, ulong)
    XBGAS_DECL_COLLECT(long, long)
    XBGAS_DECL_COLLECT(unsigned long long, ulonglong)
    XBGAS_DECL_COLLECT(long long, longlong)
    XBGAS_DECL_COLLECT(uint8_t, uint8)
    XBGAS_DECL_COLLECT(int8_t, int8)
    XBGAS_DECL_COLLECT(uint16_t, uint16)
    XBGAS_DECL_COLLECT(int16_t, int16)
    XBGAS_DECL_COLLECT(uint32_t, uint32)
    XBGAS_DECL_COLLECT(int32_t, int32)
    XBGAS_DECL_COLLECT(uint64_t, uint64)
    XBGAS_DECL_COLLECT(int64_t, int64)
    XBGAS_DECL_COLLECT(size_t, size)
    XBGAS_DECL_COLLECT(ptrdiff_t, ptrdiff)

#undef XBGAS_DECL_COLLECT


/*!   \fn xbrtime_TYPENAME_FUNC_reduce( TYPE *dest, const TYPE *src, size_t nreduce )
      \brief Performs reduction operation FUNC (sum, product, min, max, and, or, xor) on one or more values of type TYPE
      \param dest is the symmetric address of an array, of length nreduce elements, to receive the result of the reduction routines
      \param src is the symmetric address of an array, of length nreduce elements, that contains one element for each separate reduction routine
      \param nreduce is the number of elements in the dest and source arrays
      \return int Zero on successful local completion. Nonzero otherwise
*/
#define XBGAS_DECL_REDUCTION(_type, _typename, _funcname)                                 \
int xbrtime_##_typename##_##_funcname##_reduce(_type *dest, const _type *src, size_t nreduce);

    /* Sum */
    XBGAS_DECL_REDUCTION(float, float, sum)
    XBGAS_DECL_REDUCTION(double, double, sum)
    XBGAS_DECL_REDUCTION(char, char, sum)
    XBGAS_DECL_REDUCTION(unsigned char, uchar, sum)
    XBGAS_DECL_REDUCTION(signed char, schar, sum)
    XBGAS_DECL_REDUCTION(unsigned short, ushort, sum)
    XBGAS_DECL_REDUCTION(short, short, sum)
    XBGAS_DECL_REDUCTION(unsigned int, uint, sum)
    XBGAS_DECL_REDUCTION(int, int, sum)
    XBGAS_DECL_REDUCTION(unsigned long, ulong, sum)
    XBGAS_DECL_REDUCTION(long, long, sum)
    XBGAS_DECL_REDUCTION(unsigned long long, ulonglong, sum)
    XBGAS_DECL_REDUCTION(long long, longlong, sum)
    XBGAS_DECL_REDUCTION(uint8_t, uint8, sum)
    XBGAS_DECL_REDUCTION(int8_t, int8, sum)
    XBGAS_DECL_REDUCTION(uint16_t, uint16, sum)
    XBGAS_DECL_REDUCTION(int16_t, int16, sum)
    XBGAS_DECL_REDUCTION(uint32_t, uint32, sum)
    XBGAS_DECL_REDUCTION(int32_t, int32, sum)
    XBGAS_DECL_REDUCTION(uint64_t, uint64, sum)
    XBGAS_DECL_REDUCTION(int64_t, int64, sum)
    XBGAS_DECL_REDUCTION(size_t, size, sum)
    XBGAS_DECL_REDUCTION(ptrdiff_t, ptrdiff, sum)

    /* Product */
    XBGAS_DECL_REDUCTION(float, float, product)
    XBGAS_DECL_REDUCTION(double, double, product)
    XBGAS_DECL_REDUCTION(char, char, product)
    XBGAS_DECL_REDUCTION(unsigned char, uchar, product)
    XBGAS_DECL_REDUCTION(signed char, schar, product)
    XBGAS_DECL_REDUCTION(unsigned short, ushort, product)
    XBGAS_DECL_REDUCTION(short, short, product)
    XBGAS_DECL_REDUCTION(unsigned int, uint, product)
    XBGAS_DECL_REDUCTION(int, int, product)
    XBGAS_DECL_REDUCTION(unsigned long, ulong, product)
    XBGAS_DECL_REDUCTION(long, long, product)
    XBGAS_DECL_REDUCTION(unsigned long long, ulonglong, product)
    XBGAS_DECL_REDUCTION(long long, longlong, product)
    XBGAS_DECL_REDUCTION(uint8_t, uint8, product)
    XBGAS_DECL_REDUCTION(int8_t, int8, product)
    XBGAS_DECL_REDUCTION(uint16_t, uint16, product)
    XBGAS_DECL_REDUCTION(int16_t, int16, product)
    XBGAS_DECL_REDUCTION(uint32_t, uint32, product)
    XBGAS_DECL_REDUCTION(int32_t, int32, product)
    XBGAS_DECL_REDUCTION(uint64_t, uint64, product)
    XBGAS_DECL_REDUCTION(int64_t, int64, product)
    XBGAS_DECL_REDUCTION(size_t, size, product)
    XBGAS_DECL_REDUCTION(ptrdiff_t, ptrdiff, product)

    /* Max */
    XBGAS_DECL_REDUCTION(float, float, max)
    XBGAS_DECL_REDUCTION(double, double, max)
    XBGAS_DECL_REDUCTION(char, char, max)
    XBGAS_DECL_REDUCTION(unsigned char, uchar, max)
    XBGAS_DECL_REDUCTION(signed char, schar, max)
    XBGAS_DECL_REDUCTION(unsigned short, ushort, max)
    XBGAS_DECL_REDUCTION(short, short, max)
    XBGAS_DECL_REDUCTION(unsigned int, uint, max)
    XBGAS_DECL_REDUCTION(int, int, max)
    XBGAS_DECL_REDUCTION(unsigned long, ulong, max)
    XBGAS_DECL_REDUCTION(long, long, max)
    XBGAS_DECL_REDUCTION(unsigned long long, ulonglong, max)
    XBGAS_DECL_REDUCTION(long long, longlong, max)
    XBGAS_DECL_REDUCTION(uint8_t, uint8, max)
    XBGAS_DECL_REDUCTION(int8_t, int8, max)
    XBGAS_DECL_REDUCTION(uint16_t, uint16, max)
    XBGAS_DECL_REDUCTION(int16_t, int16, max)
    XBGAS_DECL_REDUCTION(uint32_t, uint32, max)
    XBGAS_DECL_REDUCTION(int32_t, int32, max)
    XBGAS_DECL_REDUCTION(uint64_t, uint64, max)
    XBGAS_DECL_REDUCTION(int64_t, int64, max)
    XBGAS_DECL_REDUCTION(size_t, size, max)
    XBGAS_DECL_REDUCTION(ptrdiff_t, ptrdiff, max)

    /* Min */
    XBGAS_DECL_REDUCTION(float, float, min)
    XBGAS_DECL_REDUCTION(double, double, min)
    XBGAS_DECL_REDUCTION(char, char, min)
    XBGAS_DECL_REDUCTION(unsigned char, uchar, min)
    XBGAS_DECL_REDUCTION(signed char, schar, min)
    XBGAS_DECL_REDUCTION(unsigned short, ushort, min)
    XBGAS_DECL_REDUCTION(short, short, min)
    XBGAS_DECL_REDUCTION(unsigned int, uint, min)
    XBGAS_DECL_REDUCTION(int, int, min)
    XBGAS_DECL_REDUCTION(unsigned long, ulong, min)
    XBGAS_DECL_REDUCTION(long, long, min)
    XBGAS_DECL_REDUCTION(unsigned long long, ulonglong, min)
    XBGAS_DECL_REDUCTION(long long, longlong, min)
    XBGAS_DECL_REDUCTION(uint8_t, uint8, min)
    XBGAS_DECL_REDUCTION(int8_t, int8, min)
    XBGAS_DECL_REDUCTION(uint16_t, uint16, min)
    XBGAS_DECL_REDUCTION(int16_t, int16, min)
    XBGAS_DECL_REDUCTION(uint32_t, uint32, min)
    XBGAS_DECL_REDUCTION(int32_t, int32, min)
    XBGAS_DECL_REDUCTION(uint64_t, uint64, min)
    XBGAS_DECL_REDUCTION(int64_t, int64, min)
    XBGAS_DECL_REDUCTION(size_t, size, min)
    XBGAS_DECL_REDUCTION(ptrdiff_t, ptrdiff, min)

    /* Binary AND */
    XBGAS_DECL_REDUCTION(unsigned char, uchar, and)
    XBGAS_DECL_REDUCTION(unsigned short, ushort, and)
    XBGAS_DECL_REDUCTION(unsigned int, uint, and)
    XBGAS_DECL_REDUCTION(unsigned long, ulong, and)
    XBGAS_DECL_REDUCTION(unsigned long long, ulonglong, and)
    XBGAS_DECL_REDUCTION(uint8_t, uint8, and)
    XBGAS_DECL_REDUCTION(int8_t, int8, and)
    XBGAS_DECL_REDUCTION(uint16_t, uint16, and)
    XBGAS_DECL_REDUCTION(int16_t, int16, and)
    XBGAS_DECL_REDUCTION(uint32_t, uint32, and)
    XBGAS_DECL_REDUCTION(int32_t, int32, and)
    XBGAS_DECL_REDUCTION(uint64_t, uint64, and)
    XBGAS_DECL_REDUCTION(int64_t, int64, and)
    XBGAS_DECL_REDUCTION(size_t, size, and)

    /* Binary OR */
    XBGAS_DECL_REDUCTION(unsigned char, uchar, or)
    XBGAS_DECL_REDUCTION(unsigned short, ushort, or)
    XBGAS_DECL_REDUCTION(unsigned int, uint, or)
    XBGAS_DECL_REDUCTION(unsigned long, ulong, or)
    XBGAS_DECL_REDUCTION(unsigned long long, ulonglong, or)
    XBGAS_DECL_REDUCTION(uint8_t, uint8, or)
    XBGAS_DECL_REDUCTION(int8_t, int8, or)
    XBGAS_DECL_REDUCTION(uint16_t, uint16, or)
    XBGAS_DECL_REDUCTION(int16_t, int16, or)
    XBGAS_DECL_REDUCTION(uint32_t, uint32, or)
    XBGAS_DECL_REDUCTION(int32_t, int32, or)
    XBGAS_DECL_REDUCTION(uint64_t, uint64, or)
    XBGAS_DECL_REDUCTION(int64_t, int64, or)
    XBGAS_DECL_REDUCTION(size_t, size, or)

    /* Binary XOR */
    XBGAS_DECL_REDUCTION(unsigned char, uchar, xor)
    XBGAS_DECL_REDUCTION(unsigned short, ushort, xor)
    XBGAS_DECL_REDUCTION(unsigned int, uint, xor)
    XBGAS_DECL_REDUCTION(unsigned long, ulong, xor)
    XBGAS_DECL_REDUCTION(unsigned long long, ulonglong, xor)
    XBGAS_DECL_REDUCTION(uint8_t, uint8, xor)
    XBGAS_DECL_REDUCTION(int8_t, int8, xor)
    XBGAS_DECL_REDUCTION(uint16_t, uint16, xor)
    XBGAS_DECL_REDUCTION(int16_t, int16, xor)
    XBGAS_DECL_REDUCTION(uint32_t, uint32, xor)
    XBGAS_DECL_REDUCTION(int32_t, int32, xor)
    XBGAS_DECL_REDUCTION(uint64_t, uint64, xor)
    XBGAS_DECL_REDUCTION(int64_t, int64, xor)
    XBGAS_DECL_REDUCTION(size_t, size, xor)  

#undef XBGAS_DECL_REDUCTION

/*!   \fn xbrtime_TYPENAME_scatter( TYPE *dest, TYPE *src, int *pe_msg_sz, int *pe_disp, size_t nelems, int root )
      \brief Independently distributes values of type TYPE located contiguously on root to each PE
      \param dest is a pointer to the base shared address on each PE where scattered values are to be stored
      \param src is a pointer to the base shared address on the root PE where values to be scattered are initially located
      \param pe_msg_sz is a pointer to an array containing the number of elements to be scattered to each PE (indexed by PE id)
      \param pe_disp is a pointer to an array containing index offsets (from src) at which each PE's messages are initially stored (indexed by PE id)
      \param nelems is the total number of elements to be scattered from the root PE
      \param root is the PE id of the root PE
      \return void
*/
#define XBGAS_DECL_SCATTER(_type, _typename)                                                                                    \
void xbrtime_##_typename##_scatter_tree(_type *dest, const _type *src, int *pe_msg_sz, int *pe_disp, size_t nelems, int root);  \
void xbrtime_##_typename##_scatter(_type *dest, const _type *src, int *pe_msg_sz, int *pe_disp, size_t nelems, int root);

    XBGAS_DECL_SCATTER(float, float)
    XBGAS_DECL_SCATTER(double, double)
    XBGAS_DECL_SCATTER(char, char)
    XBGAS_DECL_SCATTER(unsigned char, uchar)
    XBGAS_DECL_SCATTER(signed char, schar)
    XBGAS_DECL_SCATTER(unsigned short, ushort)
    XBGAS_DECL_SCATTER(short, short)
    XBGAS_DECL_SCATTER(unsigned int, uint)
    XBGAS_DECL_SCATTER(int, int)
    XBGAS_DECL_SCATTER(unsigned long, ulong)
    XBGAS_DECL_SCATTER(long, long)
    XBGAS_DECL_SCATTER(unsigned long long, ulonglong)
    XBGAS_DECL_SCATTER(long long, longlong)
    XBGAS_DECL_SCATTER(uint8_t, uint8)
    XBGAS_DECL_SCATTER(int8_t, int8)
    XBGAS_DECL_SCATTER(uint16_t, uint16)
    XBGAS_DECL_SCATTER(int16_t, int16)
    XBGAS_DECL_SCATTER(uint32_t, uint32)
    XBGAS_DECL_SCATTER(int32_t, int32)
    XBGAS_DECL_SCATTER(uint64_t, uint64)
    XBGAS_DECL_SCATTER(int64_t, int64)
    XBGAS_DECL_SCATTER(size_t, size)
    XBGAS_DECL_SCATTER(ptrdiff_t, ptrdiff)

#undef XBGAS_DECL_SCATTER

/*!   \fn xbrtime_TYPENAME_gather( TYPE *dest, TYPE *src, int *pe_msg_sz, int *pe_disp, size_t nelems, int root )
      \brief Collects disparate values of type TYPE from each PE and stores contiguously on root
      \param dest is a pointer to the base shared address on root where gathered values are to be stored
      \param src is a pointer to the base shared address on each PE where values to be gathered are initially located
      \param pe_msg_sz is a pointer to an array containing the number of elements to be gathered from each PE (indexed by PE id)
      \param pe_disp is a pointer to an array containg index offsets (from dest) at which each PE's messages are to be stored on root (indexed by PE id)
      \param nelems is the total number of elements to be gathered to the root PE
      \param root is the PE id of the root PE
      \return void
*/
#define XBGAS_DECL_GATHER(_type, _typename)                                                                                     \
void xbrtime_##_typename##_gather_tree(_type *dest, const _type *src, int *pe_msg_sz, int *pe_disp, size_t nelems, int root);   \
void xbrtime_##_typename##_gather(_type *dest, const _type *src, int *pe_msg_sz, int *pe_disp, size_t nelems, int root);

    XBGAS_DECL_GATHER(float, float)
    XBGAS_DECL_GATHER(double, double)
    XBGAS_DECL_GATHER(char, char)
    XBGAS_DECL_GATHER(unsigned char, uchar)
    XBGAS_DECL_GATHER(signed char, schar)
    XBGAS_DECL_GATHER(unsigned short, ushort)
    XBGAS_DECL_GATHER(short, short)
    XBGAS_DECL_GATHER(unsigned int, uint)
    XBGAS_DECL_GATHER(int, int)
    XBGAS_DECL_GATHER(unsigned long, ulong)
    XBGAS_DECL_GATHER(long, long)
    XBGAS_DECL_GATHER(unsigned long long, ulonglong)
    XBGAS_DECL_GATHER(long long, longlong)
    XBGAS_DECL_GATHER(uint8_t, uint8)
    XBGAS_DECL_GATHER(int8_t, int8)
    XBGAS_DECL_GATHER(uint16_t, uint16)
    XBGAS_DECL_GATHER(int16_t, int16)
    XBGAS_DECL_GATHER(uint32_t, uint32)
    XBGAS_DECL_GATHER(int32_t, int32)
    XBGAS_DECL_GATHER(uint64_t, uint64)
    XBGAS_DECL_GATHER(int64_t, int64)
    XBGAS_DECL_GATHER(size_t, size)
    XBGAS_DECL_GATHER(ptrdiff_t, ptrdiff)

#undef XBGAS_DECL_GATHER

/*!   \fn xbrtime_TYPENAME_gather_all( TYPE *dest, TYPE *src, int *pe_msg_sz, int *pe_disp, size_t nelems )
      \brief Collects disparate values of type TYPE from each PE and stores contiguously on all PEs
      \param dest is a pointer to the base shared address on each PE where gathered values are to be stored
      \param src is a pointer to the base shared address on each PE where values to be gathered are initially located
      \param pe_msg_sz is a pointer to an array containing the number of elements to be gathered from each PE (indexed by PE id)
      \param pe_disp is a pointer to an array containg index offsets (from dest) at which each PE's messages are to be stored (indexed by PE id)
      \param nelems is the total number of elements to be gathered
      \return void
*/
#define XBGAS_DECL_GATHER_ALL(_type, _typename)                                                                                     \
void xbrtime_##_typename##_gather_all_bruck_concat(_type *dest, const _type *src, int *pe_msg_sz, int *pe_disp, size_t nelems);     \
void xbrtime_##_typename##_gather_all_ring(_type *dest, const _type *src, int *pe_msg_sz, int *pe_disp, size_t nelems);             \
void xbrtime_##_typename##_gather_all(_type *dest, const _type *src, int *pe_msg_sz, int *pe_disp, size_t nelems);

    XBGAS_DECL_GATHER_ALL(float, float)
    XBGAS_DECL_GATHER_ALL(double, double)
    XBGAS_DECL_GATHER_ALL(char, char)
    XBGAS_DECL_GATHER_ALL(unsigned char, uchar)
    XBGAS_DECL_GATHER_ALL(signed char, schar)
    XBGAS_DECL_GATHER_ALL(unsigned short, ushort)
    XBGAS_DECL_GATHER_ALL(short, short)
    XBGAS_DECL_GATHER_ALL(unsigned int, uint)
    XBGAS_DECL_GATHER_ALL(int, int)
    XBGAS_DECL_GATHER_ALL(unsigned long, ulong)
    XBGAS_DECL_GATHER_ALL(long, long)
    XBGAS_DECL_GATHER_ALL(unsigned long long, ulonglong)
    XBGAS_DECL_GATHER_ALL(long long, longlong)
    XBGAS_DECL_GATHER_ALL(uint8_t, uint8)
    XBGAS_DECL_GATHER_ALL(int8_t, int8)
    XBGAS_DECL_GATHER_ALL(uint16_t, uint16)
    XBGAS_DECL_GATHER_ALL(int16_t, int16)
    XBGAS_DECL_GATHER_ALL(uint32_t, uint32)
    XBGAS_DECL_GATHER_ALL(int32_t, int32)
    XBGAS_DECL_GATHER_ALL(uint64_t, uint64)
    XBGAS_DECL_GATHER_ALL(int64_t, int64)
    XBGAS_DECL_GATHER_ALL(size_t, size)
    XBGAS_DECL_GATHER_ALL(ptrdiff_t, ptrdiff)

#undef XBGAS_DECL_GATHER_ALL

/*!   \fn xbrtime_TYPENAME_alltoall( TYPE *dest, const TYPE *src, size_t nelems, int stride )
      \brief Performs a personalized all-to-all exchange of values of type TYPE between PEs
      \param dest is a pointer to the base shared address on each PE where exchanged values are to be stored (indexed by PE id)
      \param src is a pointer to the base shared address on each PE where values to be exchanged are initially located (indexed by PE id)
      \param nelems is the number of elements being exchanged with each PE
      \return void
*/
#define XBGAS_DECL_ALLTOALL(_type, _typename)                                     \
void xbrtime_##_typename##_alltoall(_type *dest, const _type *src, size_t nelems);

    XBGAS_DECL_ALLTOALL(float, float)
    XBGAS_DECL_ALLTOALL(double, double)
    XBGAS_DECL_ALLTOALL(char, char)
    XBGAS_DECL_ALLTOALL(unsigned char, uchar)
    XBGAS_DECL_ALLTOALL(signed char, schar)
    XBGAS_DECL_ALLTOALL(unsigned short, ushort)
    XBGAS_DECL_ALLTOALL(short, short)
    XBGAS_DECL_ALLTOALL(unsigned int, uint)
    XBGAS_DECL_ALLTOALL(int, int)
    XBGAS_DECL_ALLTOALL(unsigned long, ulong)
    XBGAS_DECL_ALLTOALL(long, long)
    XBGAS_DECL_ALLTOALL(unsigned long long, ulonglong)
    XBGAS_DECL_ALLTOALL(long long, longlong)
    XBGAS_DECL_ALLTOALL(uint8_t, uint8)
    XBGAS_DECL_ALLTOALL(int8_t, int8)
    XBGAS_DECL_ALLTOALL(uint16_t, uint16)
    XBGAS_DECL_ALLTOALL(int16_t, int16)
    XBGAS_DECL_ALLTOALL(uint32_t, uint32)
    XBGAS_DECL_ALLTOALL(int32_t, int32)
    XBGAS_DECL_ALLTOALL(uint64_t, uint64)
    XBGAS_DECL_ALLTOALL(int64_t, int64)
    XBGAS_DECL_ALLTOALL(size_t, size)
    XBGAS_DECL_ALLTOALL(ptrdiff_t, ptrdiff)

#undef XBGAS_DECL_ALLTOALL

/*!   \fn xbrtime_TYPENAME_alltoalls( TYPE *dest, const TYPE *src, size_t nelems, int stride )
      \brief Performs a personalized all-to-all exchange of values of type TYPE between PEs
      \param dest is a pointer to the base shared address on each PE where exchanged values are to be stored (indexed by PE id)
      \param src is a pointer to the base shared address on each PE where values to be exchanged are initially located (indexed by PE id)
      \param dest_stride is the stride size between elements at dest
      \param src_stride is the stride size between elements at src
      \param nelems is the number of elements being exchanged with each PE
      \return void
*/
#define XBGAS_DECL_ALLTOALLS(_type, _typename)                                                                                  \
void xbrtime_##_typename##_alltoalls(_type *dest, const _type *src, ptrdiff_t src_stride, ptrdiff_t dest_stride, size_t nelems);

    XBGAS_DECL_ALLTOALLS(float, float)
    XBGAS_DECL_ALLTOALLS(double, double)
    XBGAS_DECL_ALLTOALLS(char, char)
    XBGAS_DECL_ALLTOALLS(unsigned char, uchar)
    XBGAS_DECL_ALLTOALLS(signed char, schar)
    XBGAS_DECL_ALLTOALLS(unsigned short, ushort)
    XBGAS_DECL_ALLTOALLS(short, short)
    XBGAS_DECL_ALLTOALLS(unsigned int, uint)
    XBGAS_DECL_ALLTOALLS(int, int)
    XBGAS_DECL_ALLTOALLS(unsigned long, ulong)
    XBGAS_DECL_ALLTOALLS(long, long)
    XBGAS_DECL_ALLTOALLS(unsigned long long, ulonglong)
    XBGAS_DECL_ALLTOALLS(long long, longlong)
    XBGAS_DECL_ALLTOALLS(uint8_t, uint8)
    XBGAS_DECL_ALLTOALLS(int8_t, int8)
    XBGAS_DECL_ALLTOALLS(uint16_t, uint16)
    XBGAS_DECL_ALLTOALLS(int16_t, int16)
    XBGAS_DECL_ALLTOALLS(uint32_t, uint32)
    XBGAS_DECL_ALLTOALLS(int32_t, int32)
    XBGAS_DECL_ALLTOALLS(uint64_t, uint64)
    XBGAS_DECL_ALLTOALLS(int64_t, int64)
    XBGAS_DECL_ALLTOALLS(size_t, size)
    XBGAS_DECL_ALLTOALLS(ptrdiff_t, ptrdiff)

#undef XBGAS_DECL_ALLTOALLS

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _XBRTIME_COLLECTIVES_H_ */

/* EOF */
