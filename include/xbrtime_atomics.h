/*
 * _XBRTIME_ATOMICS_H_
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

#ifndef _XBRTIME_ATOMICS_H_
#define _XBRTIME_ATOMICS_H_

#ifdef __cplusplus
extern "C" {
#endif

/*!   \fn xbrtime_TYPENAME_atomic_OP( TYPE *dest, TYPE op_val, int pe )
      \brief Performs an atomic memory operation on a remote pe; OP is one of {add, or, and, xor}
      \param dest is a pointer to the base shared address on the target PE where the atomic operation is to be performed
      \param op_val is a provdied operand for the atomic operation
      \param pe is the id of the target remote pe
      \return value at dest before OP
*/
#define XBGAS_DECL_ATOMIC_OP(_type, _typename, _op)                        \
_type xbrtime_##_typename##_atomic_##_op(_type *dest, _type op_val, int pe);

    /* Atomic add */
    XBGAS_DECL_ATOMIC_OP(int, int, add)
    XBGAS_DECL_ATOMIC_OP(long, long, add)
    XBGAS_DECL_ATOMIC_OP(long long, longlong, add)
    XBGAS_DECL_ATOMIC_OP(unsigned int, uint, add)
    XBGAS_DECL_ATOMIC_OP(unsigned long, ulong, add)
    XBGAS_DECL_ATOMIC_OP(unsigned long long, ulonglong, add)
    XBGAS_DECL_ATOMIC_OP(int32_t, int32, add)
    XBGAS_DECL_ATOMIC_OP(uint32_t, uint32, add)
    XBGAS_DECL_ATOMIC_OP(int64_t, int64, add)
    XBGAS_DECL_ATOMIC_OP(uint64_t, uint64, add)
    XBGAS_DECL_ATOMIC_OP(size_t, size, add)
    XBGAS_DECL_ATOMIC_OP(ptrdiff_t, ptrdiff, add)

    /* Atomic logical and */
    XBGAS_DECL_ATOMIC_OP(unsigned int, uint, and)
    XBGAS_DECL_ATOMIC_OP(unsigned long, ulong, and)
    XBGAS_DECL_ATOMIC_OP(unsigned long long, ulonglong, and)
    XBGAS_DECL_ATOMIC_OP(int32_t, int32, and)
    XBGAS_DECL_ATOMIC_OP(uint32_t, uint32, and)
    XBGAS_DECL_ATOMIC_OP(int64_t, int64, and)
    XBGAS_DECL_ATOMIC_OP(uint64_t, uint64, and)

    /* Atomic logical or */
    XBGAS_DECL_ATOMIC_OP(unsigned int, uint, or)
    XBGAS_DECL_ATOMIC_OP(unsigned long, ulong, or)
    XBGAS_DECL_ATOMIC_OP(unsigned long long, ulonglong, or)
    XBGAS_DECL_ATOMIC_OP(int32_t, int32, or)
    XBGAS_DECL_ATOMIC_OP(uint32_t, uint32, or)
    XBGAS_DECL_ATOMIC_OP(int64_t, int64, or)
    XBGAS_DECL_ATOMIC_OP(uint64_t, uint64, or)

    /* Atomic logical exclusive or */
    XBGAS_DECL_ATOMIC_OP(unsigned int, uint, xor)
    XBGAS_DECL_ATOMIC_OP(unsigned long, ulong, xor)
    XBGAS_DECL_ATOMIC_OP(unsigned long long, ulonglong, xor)
    XBGAS_DECL_ATOMIC_OP(int32_t, int32, xor)
    XBGAS_DECL_ATOMIC_OP(uint32_t, uint32, xor)
    XBGAS_DECL_ATOMIC_OP(int64_t, int64, xor)
    XBGAS_DECL_ATOMIC_OP(uint64_t, uint64, xor)

#undef XBGAS_DECL_ATOMIC_OP


/*!   \fn xbrtime_TYPENAME_atomic_fetch( TYPE *source, int pe )
      \brief Atomically fetches the value of a remote data object.
      \param source is the symmetric address of the source data object.
      \param pe is the id of the target remote pe.
      \return the contents at the source address on the remote PE.
*/
#define XBGAS_DECL_ATOMIC_FETCH(_type, _typename)              \
_type xbrtime_##_typename##_atomic_fetch(_type *source, int pe);

    /* Atomic fetch */
    XBGAS_DECL_ATOMIC_FETCH(float, float)
    XBGAS_DECL_ATOMIC_FETCH(double, double)
    XBGAS_DECL_ATOMIC_FETCH(int, int)
    XBGAS_DECL_ATOMIC_FETCH(long, long)
    XBGAS_DECL_ATOMIC_FETCH(long long, longlong)
    XBGAS_DECL_ATOMIC_FETCH(unsigned int, uint)
    XBGAS_DECL_ATOMIC_FETCH(unsigned long, ulong)
    XBGAS_DECL_ATOMIC_FETCH(unsigned long long, ulonglong)
    XBGAS_DECL_ATOMIC_FETCH(int32_t, int32)
    XBGAS_DECL_ATOMIC_FETCH(int64_t, int64)
    XBGAS_DECL_ATOMIC_FETCH(uint32_t, uint32)
    XBGAS_DECL_ATOMIC_FETCH(uint64_t, uint64)
    XBGAS_DECL_ATOMIC_FETCH(size_t, size)
    XBGAS_DECL_ATOMIC_FETCH(ptrdiff_t, ptrdiff)

#undef XBGAS_DECL_ATOMIC_FETCH

/*!   \fn xbrtime_TYPENAME_atomic_set( TYPE *dest, TYPE value, int pe )
      \brief Atomically sets the value of a remote data object.
      \param dest is the symmetric address of the destination data object.
      \param value is the operand to the atomic set operation.
      \param pe is the id of the target remote pe.
      \return None.
*/
#define XBGAS_DECL_ATOMIC_SET(_type, _typename)                        \
void xbrtime_##_typename##_atomic_set(_type *dest, _type value, int pe);

    /* Atomic fetch */
    XBGAS_DECL_ATOMIC_SET(float, float)
    XBGAS_DECL_ATOMIC_SET(double, double)
    XBGAS_DECL_ATOMIC_SET(int, int)
    XBGAS_DECL_ATOMIC_SET(long, long)
    XBGAS_DECL_ATOMIC_SET(long long, longlong)
    XBGAS_DECL_ATOMIC_SET(unsigned int, uint)
    XBGAS_DECL_ATOMIC_SET(unsigned long, ulong)
    XBGAS_DECL_ATOMIC_SET(unsigned long long, ulonglong)
    XBGAS_DECL_ATOMIC_SET(int32_t, int32)
    XBGAS_DECL_ATOMIC_SET(int64_t, int64)
    XBGAS_DECL_ATOMIC_SET(uint32_t, uint32)
    XBGAS_DECL_ATOMIC_SET(uint64_t, uint64)
    XBGAS_DECL_ATOMIC_SET(size_t, size)
    XBGAS_DECL_ATOMIC_SET(ptrdiff_t, ptrdiff)

#undef XBGAS_DECL_ATOMIC_SET

/*!   \fn xbrtime_TYPENAME_atomic_compare_swap( TYPE *dest, TYPE cond, TYPE value, int pe )
      \brief Performs an atomic compare & swap operation on a remote data object
      \param dest is the symmetric address of the destination data object.
      \param cond is compared to the remote dest value. If cond and the remote dest are equal, then value is swapped into the remote dest; otherwise, the remote dest is unchanged.
      \param pe is the id of the target remote pe.
      \return the contents that had been in the dest data object on the remote PE prior to the conditional swap.
*/
#define XBGAS_DECL_ATOMIC_CAS(_type, _typename)                                              \
_type xbrtime_##_typename##_atomic_compare_swap(_type *dest, _type cond, _type value, int pe);

    /* Atomic compare and swap */
    XBGAS_DECL_ATOMIC_CAS(int, int)
    XBGAS_DECL_ATOMIC_CAS(long, long)
    XBGAS_DECL_ATOMIC_CAS(long long, longlong)
    XBGAS_DECL_ATOMIC_CAS(unsigned int, uint)
    XBGAS_DECL_ATOMIC_CAS(unsigned long, ulong)
    XBGAS_DECL_ATOMIC_CAS(unsigned long long, ulonglong)
    XBGAS_DECL_ATOMIC_CAS(int32_t, int32)
    XBGAS_DECL_ATOMIC_CAS(int64_t, int64)
    XBGAS_DECL_ATOMIC_CAS(uint32_t, uint32)
    XBGAS_DECL_ATOMIC_CAS(uint64_t, uint64)
    XBGAS_DECL_ATOMIC_CAS(size_t, size)
    XBGAS_DECL_ATOMIC_CAS(ptrdiff_t, ptrdiff)

#undef XBGAS_DECL_ATOMIC_CAS

/*!   \fn xbrtime_TYPENAME_atomic_swap( TYPE *dest, TYPE value, int pe )
      \brief Performs an atomic swap to a remote data object.
      \param dest is the symmetric address of the destination data object.
      \param value is the operand to the atomic swap operation.
      \param pe is the id of the target remote pe.
      \return the contents that had been at the dest address on the remote PE prior to the swap is returned.
*/
#define XBGAS_DECL_ATOMIC_SWAP(_type, _typename)                        \
_type xbrtime_##_typename##_atomic_swap(_type *dest, _type value, int pe);

    /* Atomic swap */
    XBGAS_DECL_ATOMIC_SWAP(float, float)
    XBGAS_DECL_ATOMIC_SWAP(double, double)
    XBGAS_DECL_ATOMIC_SWAP(int, int)
    XBGAS_DECL_ATOMIC_SWAP(long, long)
    XBGAS_DECL_ATOMIC_SWAP(long long, longlong)
    XBGAS_DECL_ATOMIC_SWAP(unsigned int, uint)
    XBGAS_DECL_ATOMIC_SWAP(unsigned long, ulong)
    XBGAS_DECL_ATOMIC_SWAP(unsigned long long, ulonglong)
    XBGAS_DECL_ATOMIC_SWAP(int32_t, int32)
    XBGAS_DECL_ATOMIC_SWAP(int64_t, int64)
    XBGAS_DECL_ATOMIC_SWAP(uint32_t, uint32)
    XBGAS_DECL_ATOMIC_SWAP(uint64_t, uint64)
    XBGAS_DECL_ATOMIC_SWAP(size_t, size)
    XBGAS_DECL_ATOMIC_SWAP(ptrdiff_t, ptrdiff)

#undef XBGAS_DECL_ATOMIC_SWAP

/*!   \fn xbrtime_TYPENAME_atomic_fetch_inc( TYPE *source, int pe )
      \brief Performs an atomic fetch-and-increment operation on a remote data object.
      \param dest is the symmetric address of the destination data object.
      \param pe is the id of the target remote pe.
      \return the contents that had been at the dest address on the remote PE prior to the increment.
*/
#define XBGAS_DECL_ATOMIC_FETCH_INC(_type, _typename)            \
_type xbrtime_##_typename##_atomic_fetch_inc(_type *dest, int pe);

    /* Atomic fetch-and-increment*/
    XBGAS_DECL_ATOMIC_FETCH_INC(int, int)
    XBGAS_DECL_ATOMIC_FETCH_INC(long, long)
    XBGAS_DECL_ATOMIC_FETCH_INC(long long, longlong)
    XBGAS_DECL_ATOMIC_FETCH_INC(unsigned int, uint)
    XBGAS_DECL_ATOMIC_FETCH_INC(unsigned long, ulong)
    XBGAS_DECL_ATOMIC_FETCH_INC(unsigned long long, ulonglong)
    XBGAS_DECL_ATOMIC_FETCH_INC(int32_t, int32)
    XBGAS_DECL_ATOMIC_FETCH_INC(int64_t, int64)
    XBGAS_DECL_ATOMIC_FETCH_INC(uint32_t, uint32)
    XBGAS_DECL_ATOMIC_FETCH_INC(uint64_t, uint64)
    XBGAS_DECL_ATOMIC_FETCH_INC(size_t, size)
    XBGAS_DECL_ATOMIC_FETCH_INC(ptrdiff_t, ptrdiff)

#undef XBGAS_DECL_ATOMIC_FETCH_INC

/*!   \fn xbrtime_TYPENAME_atomic_fetch_inc( TYPE *source, int pe )
      \brief Performs an atomic increment operation on a remote data object.
      \param dest is the symmetric address of the destination data object.
      \param pe is the id of the target remote pe.
      \return None.
*/
#define XBGAS_DECL_ATOMIC_INC(_type, _typename)            \
void xbrtime_##_typename##_atomic_inc(_type *dest, int pe);

    /* Atomic increment*/
    XBGAS_DECL_ATOMIC_INC(int, int)
    XBGAS_DECL_ATOMIC_INC(long, long)
    XBGAS_DECL_ATOMIC_INC(long long, longlong)
    XBGAS_DECL_ATOMIC_INC(unsigned int, uint)
    XBGAS_DECL_ATOMIC_INC(unsigned long, ulong)
    XBGAS_DECL_ATOMIC_INC(unsigned long long, ulonglong)
    XBGAS_DECL_ATOMIC_INC(int32_t, int32)
    XBGAS_DECL_ATOMIC_INC(int64_t, int64)
    XBGAS_DECL_ATOMIC_INC(uint32_t, uint32)
    XBGAS_DECL_ATOMIC_INC(uint64_t, uint64)
    XBGAS_DECL_ATOMIC_INC(size_t, size)
    XBGAS_DECL_ATOMIC_INC(ptrdiff_t, ptrdiff)

#undef XBGAS_DECL_ATOMIC_INC

/*!   \fn xbrtime_TYPENAME_atomic_fetch_OP( TYPE *dest, TYPE value, int pe )
      \brief Performs an atomic fetch-and-OP operation on a remote data object; OP is one of {add, sub, and, or, xor}
      \param dest is the symmetric address of the destination data object.
      \param value is the operand to the atomic fetch-and-add operation.
      \param pe is the id of the target remote pe.
      \return the contents that had been at the dest address on the remote PE prior to the fetch-and-OP is returned.
*/
#define XBGAS_DECL_ATOMIC_FETCH_OP(_type, _typename, _op)                       \
_type xbrtime_##_typename##_atomic_fetch_##_op(_type *dest, _type value, int pe);

    /* Atomic fetch-and-add */
    XBGAS_DECL_ATOMIC_FETCH_OP(int, int, add)
    XBGAS_DECL_ATOMIC_FETCH_OP(long, long, add)
    XBGAS_DECL_ATOMIC_FETCH_OP(long long, longlong, add)
    XBGAS_DECL_ATOMIC_FETCH_OP(unsigned int, uint, add)
    XBGAS_DECL_ATOMIC_FETCH_OP(unsigned long, ulong, add)
    XBGAS_DECL_ATOMIC_FETCH_OP(unsigned long long, ulonglong, add)
    XBGAS_DECL_ATOMIC_FETCH_OP(int32_t, int32, add)
    XBGAS_DECL_ATOMIC_FETCH_OP(int64_t, int64, add)
    XBGAS_DECL_ATOMIC_FETCH_OP(uint32_t, uint32, add)
    XBGAS_DECL_ATOMIC_FETCH_OP(uint64_t, uint64, add)
    XBGAS_DECL_ATOMIC_FETCH_OP(size_t, size, add)
    XBGAS_DECL_ATOMIC_FETCH_OP(ptrdiff_t, ptrdiff, add)

    /* Atomic fetch-and-and */
    XBGAS_DECL_ATOMIC_FETCH_OP(unsigned int, uint, and)
    XBGAS_DECL_ATOMIC_FETCH_OP(unsigned long, ulong, and)
    XBGAS_DECL_ATOMIC_FETCH_OP(unsigned long long, ulonglong, and)
    XBGAS_DECL_ATOMIC_FETCH_OP(int32_t, int32, and)
    XBGAS_DECL_ATOMIC_FETCH_OP(int64_t, int64, and)
    XBGAS_DECL_ATOMIC_FETCH_OP(uint32_t, uint32, and)
    XBGAS_DECL_ATOMIC_FETCH_OP(uint64_t, uint64, and)

    /* Atomic fetch-and-or */
    XBGAS_DECL_ATOMIC_FETCH_OP(unsigned int, uint, or)
    XBGAS_DECL_ATOMIC_FETCH_OP(unsigned long, ulong, or)
    XBGAS_DECL_ATOMIC_FETCH_OP(unsigned long long, ulonglong, or)
    XBGAS_DECL_ATOMIC_FETCH_OP(int32_t, int32, or)
    XBGAS_DECL_ATOMIC_FETCH_OP(int64_t, int64, or)
    XBGAS_DECL_ATOMIC_FETCH_OP(uint32_t, uint32, or)
    XBGAS_DECL_ATOMIC_FETCH_OP(uint64_t, uint64, or)

    /* Atomic fetch-and-xor */
    XBGAS_DECL_ATOMIC_FETCH_OP(unsigned int, uint, xor)
    XBGAS_DECL_ATOMIC_FETCH_OP(unsigned long, ulong, xor)
    XBGAS_DECL_ATOMIC_FETCH_OP(unsigned long long, ulonglong, xor)
    XBGAS_DECL_ATOMIC_FETCH_OP(int32_t, int32, xor)
    XBGAS_DECL_ATOMIC_FETCH_OP(int64_t, int64, xor)
    XBGAS_DECL_ATOMIC_FETCH_OP(uint32_t, uint32, xor)
    XBGAS_DECL_ATOMIC_FETCH_OP(uint64_t, uint64, xor)

#undef XBGAS_DECL_ATOMIC_FETCH_OP

    
#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _XBRTIME_ATOMICS_H_ */

/* EOF */
