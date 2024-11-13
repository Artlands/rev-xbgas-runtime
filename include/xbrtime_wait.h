/*
 * _XBRTIME_WAIT_H_
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

#ifndef _XBRTIME_WAIT_H_
#define _XBRTIME_WAIT_H_

#ifdef __cplusplus
extern "C" {
#endif

/*!   \fn xbrtime_TYPENAME_wait_until( _type *ivar, int cmp, _type cmp_value )
      \brief The wait_until operation blocks until the value contained in the symmetric data object, ivar, at the calling PE satisfies the wait condition. 
      \param ivar is the symmetric address of a remotely accessible data object.
      \param cmp is the compare operator that compares ivar with cmp_value
      \param cmp_value is the value to be compared with ivar.
      \return void
*/
#define XBGAS_DECL_WAIT_UNTIL(_type, _typename)                             \
void xbrtime_##_typename##_wait_until(_type *ivar, int cmp, _type cmp_value);       

    /* Wait until operations */
    XBGAS_DECL_WAIT_UNTIL(int, int)
    XBGAS_DECL_WAIT_UNTIL(long, long)
    XBGAS_DECL_WAIT_UNTIL(long long, longlong)
    XBGAS_DECL_WAIT_UNTIL(unsigned int, uint)
    XBGAS_DECL_WAIT_UNTIL(unsigned long, ulong)
    XBGAS_DECL_WAIT_UNTIL(unsigned long long, ulonglong)
    XBGAS_DECL_WAIT_UNTIL(int32_t, int32)
    XBGAS_DECL_WAIT_UNTIL(uint64_t, uint64)
    XBGAS_DECL_WAIT_UNTIL(uint32_t, uint32)
    XBGAS_DECL_WAIT_UNTIL(int64_t, int64)
    XBGAS_DECL_WAIT_UNTIL(size_t, size)
    XBGAS_DECL_WAIT_UNTIL(ptrdiff_t, ptrdiff)

#undef XBGAS_DECL_WAIT_UNTIL

/*!   \fn xbrtime_TYPENAME_wait_until_all( _type *ivars, size_t nelems, const int *status, int cmp, _type cmp_value )
      \brief The wait_until_all routine waits until all entries in the wait set specified by ivars and status have satisfied the wait condition at the calling PE.
      \param ivars is the symmetric address of an array of remotely accessible data objects.
      \param nelems is the number of elements in the ivars array
      \param status is the local address of an optional mask array of length nelems that indicates which elements in ivars are excluded from the wait set.
      \param cmp is the compare operator that compares elements of ivars with cmp_value
      \param cmp_value is the value to be compared with the objects pointed to by ivars.
      \return void
*/
#define XBGAS_DECL_WAIT_UNTIL_ALL(_type, _typename)                                                                \
void xbrtime_##_typename##_wait_until_all(_type *ivars, size_t nelems, const int *status, int cmp, _type cmp_value);       

    /* Wait until all operations */
    XBGAS_DECL_WAIT_UNTIL_ALL(int, int)
    XBGAS_DECL_WAIT_UNTIL_ALL(long, long)
    XBGAS_DECL_WAIT_UNTIL_ALL(long long, longlong)
    XBGAS_DECL_WAIT_UNTIL_ALL(unsigned int, uint)
    XBGAS_DECL_WAIT_UNTIL_ALL(unsigned long, ulong)
    XBGAS_DECL_WAIT_UNTIL_ALL(unsigned long long, ulonglong)
    XBGAS_DECL_WAIT_UNTIL_ALL(int32_t, int32)
    XBGAS_DECL_WAIT_UNTIL_ALL(uint64_t, uint64)
    XBGAS_DECL_WAIT_UNTIL_ALL(uint32_t, uint32)
    XBGAS_DECL_WAIT_UNTIL_ALL(int64_t, int64)
    XBGAS_DECL_WAIT_UNTIL_ALL(size_t, size)
    XBGAS_DECL_WAIT_UNTIL_ALL(ptrdiff_t, ptrdiff)

#undef XBGAS_DECL_WAIT_UNTIL_ALL

/*!   \fn xbrtime_TYPENAME_wait_until_any( _type *ivars, size_t nelems, const int *status, int cmp, _type cmp_value )
      \brief The wait_until_any routine waits until any one entry in the wait set specified by ivars and status satisfies the wait condition at the calling PE.
      \param ivars is the symmetric address of an array of remotely accessible data objects.
      \param nelems is the number of elements in the ivars array
      \param status is the local address of an optional mask array of length nelems that indicates which elements in ivars are excluded from the wait set.
      \param cmp is the compare operator that compares elements of ivars with cmp_value
      \param cmp_value is the value to be compared with the objects pointed to by ivars.
      \return size_t is the index of an element in the ivars array that satisfies the wait condition.
*/
#define XBGAS_DECL_WAIT_UNTIL_ANY(_type, _typename)                                                                 \
size_t xbrtime_##_typename##_wait_until_any(_type *ivars, size_t nelems, const int *status, int cmp, _type cmp_value);       

    /* Wait until any operations */
    XBGAS_DECL_WAIT_UNTIL_ANY(int, int)
    XBGAS_DECL_WAIT_UNTIL_ANY(long, long)
    XBGAS_DECL_WAIT_UNTIL_ANY(long long, longlong)
    XBGAS_DECL_WAIT_UNTIL_ANY(unsigned int, uint)
    XBGAS_DECL_WAIT_UNTIL_ANY(unsigned long, ulong)
    XBGAS_DECL_WAIT_UNTIL_ANY(unsigned long long, ulonglong)
    XBGAS_DECL_WAIT_UNTIL_ANY(int32_t, int32)
    XBGAS_DECL_WAIT_UNTIL_ANY(uint64_t, uint64)
    XBGAS_DECL_WAIT_UNTIL_ANY(uint32_t, uint32)
    XBGAS_DECL_WAIT_UNTIL_ANY(int64_t, int64)
    XBGAS_DECL_WAIT_UNTIL_ANY(size_t, size)
    XBGAS_DECL_WAIT_UNTIL_ANY(ptrdiff_t, ptrdiff)

#undef XBGAS_DECL_WAIT_UNTIL_ANY

/*!   \fn xbrtime_TYPENAME_wait_some( _type *ivars, size_t nelems, size_t *indices, const int *status, int cmp, _type cmp_value )
      \brief The wait_some routine waits until at least one entry in the wait set specified by ivars and status satisfies the wait condition at the calling PE. 
      This routine tests all elements of ivars in the wait set at least once.
      \param ivars is the symmetric address of an array of remotely accessible data objects.
      \param nelems is the number of elements in the ivars array
      \param indices is the local address of an array of length at least nelems that will contain the indices of the elements in the ivars array that satisfy the wait condition.
      \param status is the local address of an optional mask array of length nelems that indicates which elements in ivars are excluded from the wait set.
      \param cmp is the compare operator that compares elements of ivars with cmp_value
      \param cmp_value is the value to be compared with the objects pointed to by ivars.
      \return size_t is the number of indices returned in the indices array.
*/
#define XBGAS_DECL_WAIT_UNTIL_SOME(_type, _typename)                                                                                   \
size_t xbrtime_##_typename##_wait_until_some(_type *ivars, size_t nelems, size_t *indices, const int *status, int cmp, _type cmp_value);       

    /* Wait until some operations */
    XBGAS_DECL_WAIT_UNTIL_SOME(int, int)
    XBGAS_DECL_WAIT_UNTIL_SOME(long, long)
    XBGAS_DECL_WAIT_UNTIL_SOME(long long, longlong)
    XBGAS_DECL_WAIT_UNTIL_SOME(unsigned int, uint)
    XBGAS_DECL_WAIT_UNTIL_SOME(unsigned long, ulong)
    XBGAS_DECL_WAIT_UNTIL_SOME(unsigned long long, ulonglong)
    XBGAS_DECL_WAIT_UNTIL_SOME(int32_t, int32)
    XBGAS_DECL_WAIT_UNTIL_SOME(uint64_t, uint64)
    XBGAS_DECL_WAIT_UNTIL_SOME(uint32_t, uint32)
    XBGAS_DECL_WAIT_UNTIL_SOME(int64_t, int64)
    XBGAS_DECL_WAIT_UNTIL_SOME(size_t, size)
    XBGAS_DECL_WAIT_UNTIL_SOME(ptrdiff_t, ptrdiff)

#undef XBGAS_DECL_WAIT_UNTIL_SOME

/*!   \fn xbrtime_TYPENAME_wait_until_all_vector( _type *ivars, size_t nelems, const int *status, int cmp, _type *cmp_values )
      \brief the wait_until_all_vector routine waits until all entries in the wait set specified by ivars and status have satisfied the wait conditions at the calling PE. 
      This routine compares each element of the ivars array in the wait set with each respective value in cmp_values according to the comparison operator cmp at the calling PE.
      \param ivars is the symmetric address of an array of remotely accessible data objects.
      \param nelems is the number of elements in the ivars array
      \param status is the local address of an optional mask array of length nelems that indicates which elements in ivars are excluded from the wait set.
      \param cmp is the compare operator that compares elements of ivars with cmp_value
      \param *cmp_values is the local address of an array of length nelems containing values to be compared with the respective objects in ivars.
      \return void
*/
#define XBGAS_DECL_WAIT_UNTIL_ALL_VECTOR(_type, _typename)                                                                  \
void xbrtime_##_typename##_wait_until_all_vector(_type *ivars, size_t nelems, const int *status, int cmp, _type *cmp_values);       

    /* Wait until all vector operations */
    XBGAS_DECL_WAIT_UNTIL_ALL_VECTOR(int, int)
    XBGAS_DECL_WAIT_UNTIL_ALL_VECTOR(long, long)
    XBGAS_DECL_WAIT_UNTIL_ALL_VECTOR(long long, longlong)
    XBGAS_DECL_WAIT_UNTIL_ALL_VECTOR(unsigned int, uint)
    XBGAS_DECL_WAIT_UNTIL_ALL_VECTOR(unsigned long, ulong)
    XBGAS_DECL_WAIT_UNTIL_ALL_VECTOR(unsigned long long, ulonglong)
    XBGAS_DECL_WAIT_UNTIL_ALL_VECTOR(int32_t, int32)
    XBGAS_DECL_WAIT_UNTIL_ALL_VECTOR(uint64_t, uint64)
    XBGAS_DECL_WAIT_UNTIL_ALL_VECTOR(uint32_t, uint32)
    XBGAS_DECL_WAIT_UNTIL_ALL_VECTOR(int64_t, int64)
    XBGAS_DECL_WAIT_UNTIL_ALL_VECTOR(size_t, size)
    XBGAS_DECL_WAIT_UNTIL_ALL_VECTOR(ptrdiff_t, ptrdiff)

#undef XBGAS_DECL_WAIT_UNTIL_ALL_VECTOR

/*!   \fn xbrtime_TYPENAME_wait_until_any_vector( _type *ivars, size_t nelems, const int *status, int cmp, _type *cmp_values )
      \brief The wait_until_any_vector routine waits until any one entry in the wait set specified by ivars and status satisfies the wait condition at the calling PE.
      \param ivars is the symmetric address of an array of remotely accessible data objects.
      \param nelems is the number of elements in the ivars array
      \param status is the local address of an optional mask array of length nelems that indicates which elements in ivars are excluded from the wait set.
      \param cmp is the compare operator that compares elements of ivars with cmp_value
      \param *cmp_values is the local address of an array of length nelems containing values to be compared with the respective objects in ivars.
      \return size_t returns the index of an element in the ivars array that satisfies the wait condition. If the wait set is empty, this routine returns SIZE_MAX.
*/
#define XBGAS_DECL_WAIT_UNTIL_ANY_VECTOR(_type, _typename)                                                                   \
size_t xbrtime_##_typename##_wait_until_any_vector(_type *ivars, size_t nelems, const int *status, int cmp, _type *cmp_values);       

    /* Wait until any vector operations */
    XBGAS_DECL_WAIT_UNTIL_ANY_VECTOR(int, int)
    XBGAS_DECL_WAIT_UNTIL_ANY_VECTOR(long, long)
    XBGAS_DECL_WAIT_UNTIL_ANY_VECTOR(long long, longlong)
    XBGAS_DECL_WAIT_UNTIL_ANY_VECTOR(unsigned int, uint)
    XBGAS_DECL_WAIT_UNTIL_ANY_VECTOR(unsigned long, ulong)
    XBGAS_DECL_WAIT_UNTIL_ANY_VECTOR(unsigned long long, ulonglong)
    XBGAS_DECL_WAIT_UNTIL_ANY_VECTOR(int32_t, int32)
    XBGAS_DECL_WAIT_UNTIL_ANY_VECTOR(uint64_t, uint64)
    XBGAS_DECL_WAIT_UNTIL_ANY_VECTOR(uint32_t, uint32)
    XBGAS_DECL_WAIT_UNTIL_ANY_VECTOR(int64_t, int64)
    XBGAS_DECL_WAIT_UNTIL_ANY_VECTOR(size_t, size)
    XBGAS_DECL_WAIT_UNTIL_ANY_VECTOR(ptrdiff_t, ptrdiff)

#undef XBGAS_DECL_WAIT_UNTIL_ANY_VECTOR

/*!   \fn xbrtime_TYPENAME_wait_some_vector( _type *ivars, size_t nelems, size_t *indices, const int *status, int cmp, _type *cmp_value )
      \brief The wait_some_vector routine waits until at least one entry in the wait set specified by ivars and status satisfies the wait condition at the calling PE. 
      This routine tests all elements of ivars in the wait set at least once.
      \param ivars is the symmetric address of an array of remotely accessible data objects.
      \param nelems is the number of elements in the ivars array
      \param indices is the local address of an array containing the indices of at least one element in the wait set that satisfied the wait condition.
      \param status is the local address of an optional mask array of length nelems that indicates which elements in ivars are excluded from the wait set.
      \param cmp is the compare operator that compares elements of ivars with cmp_value
      \param *cmp_values is the local address of an array of length nelems containing values to be compared with the respective objects in ivars.
      \return size_t is the number of indices returned in the indices array.
*/
#define XBGAS_DECL_WAIT_UNTIL_SOME_VECTOR(_type, _typename)                                                                                    \
size_t xbrtime_##_typename##_wait_until_some_vector(_type *ivars, size_t nelems, size_t *indices, const int *status, int cmp, _type *cmp_value);       

    /* Wait until some vector operations */
    XBGAS_DECL_WAIT_UNTIL_SOME_VECTOR(int, int)
    XBGAS_DECL_WAIT_UNTIL_SOME_VECTOR(long, long)
    XBGAS_DECL_WAIT_UNTIL_SOME_VECTOR(long long, longlong)
    XBGAS_DECL_WAIT_UNTIL_SOME_VECTOR(unsigned int, uint)
    XBGAS_DECL_WAIT_UNTIL_SOME_VECTOR(unsigned long, ulong)
    XBGAS_DECL_WAIT_UNTIL_SOME_VECTOR(unsigned long long, ulonglong)
    XBGAS_DECL_WAIT_UNTIL_SOME_VECTOR(int32_t, int32)
    XBGAS_DECL_WAIT_UNTIL_SOME_VECTOR(uint64_t, uint64)
    XBGAS_DECL_WAIT_UNTIL_SOME_VECTOR(uint32_t, uint32)
    XBGAS_DECL_WAIT_UNTIL_SOME_VECTOR(int64_t, int64)
    XBGAS_DECL_WAIT_UNTIL_SOME_VECTOR(size_t, size)
    XBGAS_DECL_WAIT_UNTIL_SOME_VECTOR(ptrdiff_t, ptrdiff)

#undef XBGAS_DECL_WAIT_UNTIL_SOME_VECTOR

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _XBRTIME_WAIT_H_ */

/* EOF */