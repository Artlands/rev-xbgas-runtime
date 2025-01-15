/*
 * _XBRTIME_TEST_H_
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

#ifndef _XBRTIME_TEST_H_
#define _XBRTIME_TEST_H_

#ifdef __cplusplus
extern "C" {
#endif

/*!   \fn xbrtime_TYPENAME_test( _type *ivar, int cmp, _type cmp_value )
      \brief The test routine tests the numeric comparison of the symmetric object pointed to by ivar with the value cmp_value according to the comparison operator cmp.
      \param ivar is the symmetric address of a remotely accessible data object.
      \param cmp is the compare operator that compares ivar with cmp_value
      \param cmp_value is the value to be compared with ivar.
      \return int returns 1 if the comparison of the symmetric object pointed to by ivar with the value cmp_value according to the comparison operator cmp evaluates to true; otherwise, it returns 0.
*/
#define XBGAS_DECL_TEST(_type, _typename)                            \
int xbrtime_##_typename##_test(_type *ivar, int cmp, _type cmp_value);       

    /* Test operations */
    XBGAS_DECL_TEST(int, int)
    XBGAS_DECL_TEST(long, long)
    XBGAS_DECL_TEST(long long, longlong)
    XBGAS_DECL_TEST(unsigned int, uint)
    XBGAS_DECL_TEST(unsigned long, ulong)
    XBGAS_DECL_TEST(unsigned long long, ulonglong)
    XBGAS_DECL_TEST(int32_t, int32)
    XBGAS_DECL_TEST(uint64_t, uint64)
    XBGAS_DECL_TEST(uint32_t, uint32)
    XBGAS_DECL_TEST(int64_t, int64)
    XBGAS_DECL_TEST(size_t, size)
    XBGAS_DECL_TEST(ptrdiff_t, ptrdiff)

#undef XBGAS_DECL_TEST

/*!   \fn xbrtime_TYPENAME_test_all( _type *ivars, size_t nelems, const int *status, int cmp, _type cmp_value )
      \brief The test_all routine indicates whether all entries in the test set specified by ivars and status have satisfied the test condition at the calling PE.
      \param ivars is the symmetric address of an array of remotely accessible data objects.
      \param nelems is the number of elements in the ivars array
      \param status is the local address of an optional mask array of length nelems that indicates which elements in ivars are excluded from the test set.
      \param cmp is the compare operator that compares elements of ivars with cmp_value
      \param cmp_value is the value to be compared with the objects pointed to by ivars.
      \return int returns 1 if all variables in ivars satisfy the test condition or if nelems is 0, otherwise this routine returns 0.
*/
#define XBGAS_DECL_TEST_ALL(_type, _typename)                                                                \
int xbrtime_##_typename##_test_all(_type *ivars, size_t nelems, const int *status, int cmp, _type cmp_value);       

    /* Test all operations */
    XBGAS_DECL_TEST_ALL(int, int)
    XBGAS_DECL_TEST_ALL(long, long)
    XBGAS_DECL_TEST_ALL(long long, longlong)
    XBGAS_DECL_TEST_ALL(unsigned int, uint)
    XBGAS_DECL_TEST_ALL(unsigned long, ulong)
    XBGAS_DECL_TEST_ALL(unsigned long long, ulonglong)
    XBGAS_DECL_TEST_ALL(int32_t, int32)
    XBGAS_DECL_TEST_ALL(uint64_t, uint64)
    XBGAS_DECL_TEST_ALL(uint32_t, uint32)
    XBGAS_DECL_TEST_ALL(int64_t, int64)
    XBGAS_DECL_TEST_ALL(size_t, size)
    XBGAS_DECL_TEST_ALL(ptrdiff_t, ptrdiff)

#undef XBGAS_DECL_TEST_ALL

/*!   \fn xbrtime_TYPENAME_test_any( _type *ivars, size_t nelems, const int *status, int cmp, _type cmp_value )
      \brief The test_any routine indicates whether any entry in the test set specified by ivars and status has satisfied the test condition at the calling PE.
      \param ivars is the symmetric address of an array of remotely accessible data objects.
      \param nelems is the number of elements in the ivars array
      \param status is the local address of an optional mask array of length nelems that indicates which elements in ivars are excluded from the test set.
      \param cmp is the compare operator that compares elements of ivars with cmp_value
      \param cmp_value is the value to be compared with the objects pointed to by ivars.
      \return size_t returns the index of an element in the ivars array that satisfies the test condition. If the test set is empty or no conditions in the test set are satisfied, this routine returns SIZE_MAX.
*/
#define XBGAS_DECL_TEST_ANY(_type, _typename)                                                                  \
size_t xbrtime_##_typename##_test_any(_type *ivars, size_t nelems, const int *status, int cmp, _type cmp_value);       

    /* Test any operations */
    XBGAS_DECL_TEST_ANY(int, int)
    XBGAS_DECL_TEST_ANY(long, long)
    XBGAS_DECL_TEST_ANY(long long, longlong)
    XBGAS_DECL_TEST_ANY(unsigned int, uint)
    XBGAS_DECL_TEST_ANY(unsigned long, ulong)
    XBGAS_DECL_TEST_ANY(unsigned long long, ulonglong)
    XBGAS_DECL_TEST_ANY(int32_t, int32)
    XBGAS_DECL_TEST_ANY(uint64_t, uint64)
    XBGAS_DECL_TEST_ANY(uint32_t, uint32)
    XBGAS_DECL_TEST_ANY(int64_t, int64)
    XBGAS_DECL_TEST_ANY(size_t, size)
    XBGAS_DECL_TEST_ANY(ptrdiff_t, ptrdiff)

#undef XBGAS_DECL_TEST_ANY

/*!   \fn xbrtime_TYPENAME_test_some( _type *ivars, size_t nelems, size_t *indices, const int *status, int cmp, _type cmp_value )
      \brief The test_some routine indicates whether at least one entry in the test set specified by ivars and status has satisfied the test condition at the calling PE. 
      This routine tests all elements of ivars in the test set at least once.
      \param ivars is the symmetric address of an array of remotely accessible data objects.
      \param nelems is the number of elements in the ivars array
      \param indices is the local address of an array of length at least nelems that will contain the indices of the elements in the ivars array that satisfy the test condition.
      \param status is the local address of an optional mask array of length nelems that indicates which elements in ivars are excluded from the test set.
      \param cmp is the compare operator that compares elements of ivars with cmp_value
      \param cmp_value is the value to be compared with the objects pointed to by ivars.
      \return size_t returns the number of indices returned in the indices array. If the test set is empty, this routine returns 0.
*/
#define XBGAS_DECL_TEST_SOME(_type, _typename)                                                                                   \
size_t xbrtime_##_typename##_test_some(_type *ivars, size_t nelems, size_t *indices, const int *status, int cmp, _type cmp_value);       

    /* Test some operations */
    XBGAS_DECL_TEST_SOME(int, int)
    XBGAS_DECL_TEST_SOME(long, long)
    XBGAS_DECL_TEST_SOME(long long, longlong)
    XBGAS_DECL_TEST_SOME(unsigned int, uint)
    XBGAS_DECL_TEST_SOME(unsigned long, ulong)
    XBGAS_DECL_TEST_SOME(unsigned long long, ulonglong)
    XBGAS_DECL_TEST_SOME(int32_t, int32)
    XBGAS_DECL_TEST_SOME(uint64_t, uint64)
    XBGAS_DECL_TEST_SOME(uint32_t, uint32)
    XBGAS_DECL_TEST_SOME(int64_t, int64)
    XBGAS_DECL_TEST_SOME(size_t, size)
    XBGAS_DECL_TEST_SOME(ptrdiff_t, ptrdiff)

#undef XBGAS_DECL_TEST_SOME

/*!   \fn xbrtime_TYPENAME_test_all_vector( _type *ivars, size_t nelems, const int *status, int cmp, _type *cmp_values )
      \brief the test_all_vector routine indicates whether all entries in the test set specified by ivars and status have satisfied the test condition at the calling PE.
      This routine compares each element of the ivars array in the test set with each respective value in cmp_values according to the comparison operator cmp at the calling PE.
      \param ivars is the symmetric address of an array of remotely accessible data objects.
      \param nelems is the number of elements in the ivars array
      \param status is the local address of an optional mask array of length nelems that indicates which elements in ivars are excluded from the test set.
      \param cmp is the compare operator that compares elements of ivars with cmp_value
      \param *cmp_values is the local address of an array of length nelems containing values to be compared with the respective objects in ivars.
      \return int returns 1 if all variables in ivars satisfy the test conditions or if nelems is 0, otherwise this routine returns 0.
*/
#define XBGAS_DECL_TEST_ALL_VECTOR(_type, _typename)                                                                 \
int xbrtime_##_typename##_test_all_vector(_type *ivars, size_t nelems, const int *status, int cmp, _type *cmp_values);       

    /* Test all vector operations */
    XBGAS_DECL_TEST_ALL_VECTOR(int, int)
    XBGAS_DECL_TEST_ALL_VECTOR(long, long)
    XBGAS_DECL_TEST_ALL_VECTOR(long long, longlong)
    XBGAS_DECL_TEST_ALL_VECTOR(unsigned int, uint)
    XBGAS_DECL_TEST_ALL_VECTOR(unsigned long, ulong)
    XBGAS_DECL_TEST_ALL_VECTOR(unsigned long long, ulonglong)
    XBGAS_DECL_TEST_ALL_VECTOR(int32_t, int32)
    XBGAS_DECL_TEST_ALL_VECTOR(uint64_t, uint64)
    XBGAS_DECL_TEST_ALL_VECTOR(uint32_t, uint32)
    XBGAS_DECL_TEST_ALL_VECTOR(int64_t, int64)
    XBGAS_DECL_TEST_ALL_VECTOR(size_t, size)
    XBGAS_DECL_TEST_ALL_VECTOR(ptrdiff_t, ptrdiff)

#undef XBGAS_DECL_TEST_ALL_VECTOR

/*!   \fn xbrtime_TYPENAME_test_any_vector( _type *ivars, size_t nelems, const int *status, int cmp, _type *cmp_values )
      \brief The test_any_vector routine indicates whether any entry in the test set specified by ivars and status has satisfied the test condition at the calling PE.
      \param ivars is the symmetric address of an array of remotely accessible data objects.
      \param nelems is the number of elements in the ivars array
      \param status is the local address of an optional mask array of length nelems that indicates which elements in ivars are excluded from the test set.
      \param cmp is the compare operator that compares elements of ivars with cmp_value
      \param *cmp_values is the local address of an array of length nelems containing values to be compared with the respective objects in ivars.
      \return size_t returns the index of an element in the ivars array that satisfies the test condition. If the test set is empty or no conditions in the test set are satisfied, this routine returns SIZE_MAX.
*/
#define XBGAS_DECL_TEST_ANY_VECTOR(_type, _typename)                                                                    \
size_t xbrtime_##_typename##_test_any_vector(_type *ivars, size_t nelems, const int *status, int cmp, _type *cmp_values);       

    /* Test any vector operations */
    XBGAS_DECL_TEST_ANY_VECTOR(int, int)
    XBGAS_DECL_TEST_ANY_VECTOR(long, long)
    XBGAS_DECL_TEST_ANY_VECTOR(long long, longlong)
    XBGAS_DECL_TEST_ANY_VECTOR(unsigned int, uint)
    XBGAS_DECL_TEST_ANY_VECTOR(unsigned long, ulong)
    XBGAS_DECL_TEST_ANY_VECTOR(unsigned long long, ulonglong)
    XBGAS_DECL_TEST_ANY_VECTOR(int32_t, int32)
    XBGAS_DECL_TEST_ANY_VECTOR(uint64_t, uint64)
    XBGAS_DECL_TEST_ANY_VECTOR(uint32_t, uint32)
    XBGAS_DECL_TEST_ANY_VECTOR(int64_t, int64)
    XBGAS_DECL_TEST_ANY_VECTOR(size_t, size)
    XBGAS_DECL_TEST_ANY_VECTOR(ptrdiff_t, ptrdiff)

#undef XBGAS_DECL_TEST_ANY_VECTOR

/*!   \fn xbrtime_TYPENAME_test_some_vector( _type *ivars, size_t nelems, size_t *indices, const int *status, int cmp, _type *cmp_value )
      \brief The test_some_vector routine indicates whether at least one entry in the test set specified by ivars and status satisfies the test condition at the calling PE.
      This routine tests all elements of ivars in the test set at least once.
      \param ivars is the symmetric address of an array of remotely accessible data objects.
      \param nelems is the number of elements in the ivars array
      \param indices is the local address of an array containing the indices of at least one element in the test set that satisfied the test condition.
      \param status is the local address of an optional mask array of length nelems that indicates which elements in ivars are excluded from the test set.
      \param cmp is the compare operator that compares elements of ivars with cmp_value
      \param *cmp_values is the local address of an array of length nelems containing values to be compared with the respective objects in ivars.
      \return size_t returns the number of indices returned in the indices array. If the test set is empty, this routine returns 0.
*/
#define XBGAS_DECL_TEST_SOME_VECTOR(_type, _typename)                                                                                    \
size_t xbrtime_##_typename##_test_some_vector(_type *ivars, size_t nelems, size_t *indices, const int *status, int cmp, _type *cmp_value);       

    /* Test some vector operations */
    XBGAS_DECL_TEST_SOME_VECTOR(int, int)
    XBGAS_DECL_TEST_SOME_VECTOR(long, long)
    XBGAS_DECL_TEST_SOME_VECTOR(long long, longlong)
    XBGAS_DECL_TEST_SOME_VECTOR(unsigned int, uint)
    XBGAS_DECL_TEST_SOME_VECTOR(unsigned long, ulong)
    XBGAS_DECL_TEST_SOME_VECTOR(unsigned long long, ulonglong)
    XBGAS_DECL_TEST_SOME_VECTOR(int32_t, int32)
    XBGAS_DECL_TEST_SOME_VECTOR(uint64_t, uint64)
    XBGAS_DECL_TEST_SOME_VECTOR(uint32_t, uint32)
    XBGAS_DECL_TEST_SOME_VECTOR(int64_t, int64)
    XBGAS_DECL_TEST_SOME_VECTOR(size_t, size)
    XBGAS_DECL_TEST_SOME_VECTOR(ptrdiff_t, ptrdiff)

#undef XBGAS_DECL_TEST_SOME_VECTOR

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _XBRTIME_TEST_H_ */

/* EOF */