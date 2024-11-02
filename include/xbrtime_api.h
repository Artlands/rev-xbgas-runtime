/*
 * _XBRTIME_API_H_
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

/*!   \file xbrtime-api.h
      \brief XBGAS Runtime Data Transfer API Header File

      The XBGAS Runtime provides C/CXX level function interfaces
      for applications to conveniently utilize the shared memory
      capabilities present in the xBGAS extension to the RISC-V
      specification
*/

#ifndef _XBRTIME_API_H_
#define _XBRTIME_API_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>

/**
 * xbrtime_TYPE_MEMOP(TYPE *dest, TYPE *src, size_t nelems, int pe)
 *
 */

#define XBGAS_DECL_PUTGET(_type, _typename, _op)               \
  /**                                                          \
   * @see xbrtime_TYPE_OP                                      \
   */                                                          \
  void xbrtime_##_typename##_##_op(_type *dest,                \
                                   const _type *source,        \
                                   size_t nelems,              \
                                   int pe);                    \
                                                               \
  /**                                                          \
   * @see xbrtime_TYPE_OP_NBI                                  \
   */                                                          \
  void xbrtime_##_typename##_##_op##_nbi(_type *dest,          \
                                         const _type *source,  \
                                         size_t nelems,        \
                                         int pe);

  /* Put operation */
  XBGAS_DECL_PUTGET(float, float, put)
  XBGAS_DECL_PUTGET(double, double, put)
  XBGAS_DECL_PUTGET(long double, longdouble, put)
  XBGAS_DECL_PUTGET(char, char, put)
  XBGAS_DECL_PUTGET(signed char, schar, put)
  XBGAS_DECL_PUTGET(short, short, put)
  XBGAS_DECL_PUTGET(int, int, put)
  XBGAS_DECL_PUTGET(long, long, put)
  XBGAS_DECL_PUTGET(long long, longlong, put)
  XBGAS_DECL_PUTGET(unsigned char, uchar, put)
  XBGAS_DECL_PUTGET(unsigned short, ushort, put)
  XBGAS_DECL_PUTGET(unsigned int, uint, put)
  XBGAS_DECL_PUTGET(unsigned long, ulong, put)
  XBGAS_DECL_PUTGET(unsigned long long, ulonglong, put)
  XBGAS_DECL_PUTGET(int8_t, int8, put)
  XBGAS_DECL_PUTGET(int16_t, int16, put)
  XBGAS_DECL_PUTGET(int32_t, int32, put)
  XBGAS_DECL_PUTGET(int64_t, int64, put)
  XBGAS_DECL_PUTGET(uint8_t, uint8, put)
  XBGAS_DECL_PUTGET(uint16_t, uint16, put)
  XBGAS_DECL_PUTGET(uint32_t, uint32, put)
  XBGAS_DECL_PUTGET(uint64_t, uint64, put)
  XBGAS_DECL_PUTGET(size_t, size, put)
  XBGAS_DECL_PUTGET(ptrdiff_t, ptrdiff, put)

  /* Get operation */
  XBGAS_DECL_PUTGET(float, float, get)
  XBGAS_DECL_PUTGET(double, double, get)
  XBGAS_DECL_PUTGET(long double, longdouble, get)
  XBGAS_DECL_PUTGET(char, char, get)
  XBGAS_DECL_PUTGET(signed char, schar, get)
  XBGAS_DECL_PUTGET(short, short, get)
  XBGAS_DECL_PUTGET(int, int, get)
  XBGAS_DECL_PUTGET(long, long, get)
  XBGAS_DECL_PUTGET(long long, longlong, get)
  XBGAS_DECL_PUTGET(unsigned char, uchar, get)
  XBGAS_DECL_PUTGET(unsigned short, ushort, get)
  XBGAS_DECL_PUTGET(unsigned int, uint, get)
  XBGAS_DECL_PUTGET(unsigned long, ulong, get)
  XBGAS_DECL_PUTGET(unsigned long long, ulonglong, get)
  XBGAS_DECL_PUTGET(int8_t, int8, get)
  XBGAS_DECL_PUTGET(int16_t, int16, get)
  XBGAS_DECL_PUTGET(int32_t, int32, get)
  XBGAS_DECL_PUTGET(int64_t, int64, get)
  XBGAS_DECL_PUTGET(uint8_t, uint8, get)
  XBGAS_DECL_PUTGET(uint16_t, uint16, get)
  XBGAS_DECL_PUTGET(uint32_t, uint32, get)
  XBGAS_DECL_PUTGET(uint64_t, uint64, get)
  XBGAS_DECL_PUTGET(size_t, size, get)
  XBGAS_DECL_PUTGET(ptrdiff_t, ptrdiff, get)

#undef XBGAS_DECL_PUTGET

/**
 * xbrtime_TYPE_MEMOP(TYPE *dest, TYPE *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems, int pe)
 *
 */

#define XBGAS_DECL_I_PUTGET(_type, _typename, _op)             \
  /**                                                          \
   * @see xbrtime_TYPE_OP                                      \
   */                                                          \
  void xbrtime_##_typename##_i##_op(_type *dest,                \
                                   const _type *source,        \
                                   ptrdiff_t dst,              \
                                   ptrdiff_t sst,              \
                                   size_t nelems,              \
                                   int pe);                    


  /* Strided-Put operation */
  XBGAS_DECL_I_PUTGET(float, float, put)
  XBGAS_DECL_I_PUTGET(double, double, put)
  XBGAS_DECL_I_PUTGET(long double, longdouble, put)
  XBGAS_DECL_I_PUTGET(char, char, put)
  XBGAS_DECL_I_PUTGET(signed char, schar, put)
  XBGAS_DECL_I_PUTGET(short, short, put)
  XBGAS_DECL_I_PUTGET(int, int, put)
  XBGAS_DECL_I_PUTGET(long, long, put)
  XBGAS_DECL_I_PUTGET(long long, longlong, put)
  XBGAS_DECL_I_PUTGET(unsigned char, uchar, put)
  XBGAS_DECL_I_PUTGET(unsigned short, ushort, put)
  XBGAS_DECL_I_PUTGET(unsigned int, uint, put)
  XBGAS_DECL_I_PUTGET(unsigned long, ulong, put)
  XBGAS_DECL_I_PUTGET(unsigned long long, ulonglong, put)
  XBGAS_DECL_I_PUTGET(int8_t, int8, put)
  XBGAS_DECL_I_PUTGET(int16_t, int16, put)
  XBGAS_DECL_I_PUTGET(int32_t, int32, put)
  XBGAS_DECL_I_PUTGET(int64_t, int64, put)
  XBGAS_DECL_I_PUTGET(uint8_t, uint8, put)
  XBGAS_DECL_I_PUTGET(uint16_t, uint16, put)
  XBGAS_DECL_I_PUTGET(uint32_t, uint32, put)
  XBGAS_DECL_I_PUTGET(uint64_t, uint64, put)
  XBGAS_DECL_I_PUTGET(size_t, size, put)
  XBGAS_DECL_I_PUTGET(ptrdiff_t, ptrdiff, put)

  /* Strided-Get operation */
  XBGAS_DECL_I_PUTGET(float, float, get)
  XBGAS_DECL_I_PUTGET(double, double, get)
  XBGAS_DECL_I_PUTGET(long double, longdouble, get)
  XBGAS_DECL_I_PUTGET(char, char, get)
  XBGAS_DECL_I_PUTGET(signed char, schar, get)
  XBGAS_DECL_I_PUTGET(short, short, get)
  XBGAS_DECL_I_PUTGET(int, int, get)
  XBGAS_DECL_I_PUTGET(long, long, get)
  XBGAS_DECL_I_PUTGET(long long, longlong, get)
  XBGAS_DECL_I_PUTGET(unsigned char, uchar, get)
  XBGAS_DECL_I_PUTGET(unsigned short, ushort, get)
  XBGAS_DECL_I_PUTGET(unsigned int, uint, get)
  XBGAS_DECL_I_PUTGET(unsigned long, ulong, get)
  XBGAS_DECL_I_PUTGET(unsigned long long, ulonglong, get)
  XBGAS_DECL_I_PUTGET(int8_t, int8, get)
  XBGAS_DECL_I_PUTGET(int16_t, int16, get)
  XBGAS_DECL_I_PUTGET(int32_t, int32, get)
  XBGAS_DECL_I_PUTGET(int64_t, int64, get)
  XBGAS_DECL_I_PUTGET(uint8_t, uint8, get)
  XBGAS_DECL_I_PUTGET(uint16_t, uint16, get)
  XBGAS_DECL_I_PUTGET(uint32_t, uint32, get)
  XBGAS_DECL_I_PUTGET(uint64_t, uint64, get)
  XBGAS_DECL_I_PUTGET(size_t, size, get)
  XBGAS_DECL_I_PUTGET(ptrdiff_t, ptrdiff, get)

#undef XBGAS_DECL_I_PUTGET


#define XBGAS_DECL_PUT_SIGNAL(_type, _typename)             \
  /**                                                       \
   * @see xbrtime_TYPE_PUT_SIGNAL                           \
   */                                                       \
  void xbrtime_##_typename##put_signal(_type *dest,         \
                                        const _type *src,   \
                                        size_t nelems,      \
                                        uint64_t *sig_addr, \
                                        uint64_t signal,    \
                                        int sig_op,         \
                                        int pe);            \
                                                            \
  /**                                                       \
   * @see xbrtime_TYPE_PUT_SIGNAL_NBI                       \
   */                                                       \
  void xbrtime_##_typename##put_signal_nbi(_type *dest,     \
                                        const _type *src,   \
                                        size_t nelems,      \
                                        uint64_t *sig_addr, \
                                        uint64_t signal,    \
                                        int sig_op,         \
                                        int pe);            \

  XBGAS_DECL_PUT_SIGNAL(float, float)
  XBGAS_DECL_PUT_SIGNAL(double, double)
  XBGAS_DECL_PUT_SIGNAL(long double, longdouble)
  XBGAS_DECL_PUT_SIGNAL(char, char)
  XBGAS_DECL_PUT_SIGNAL(signed char, schar)
  XBGAS_DECL_PUT_SIGNAL(short, short)
  XBGAS_DECL_PUT_SIGNAL(int, int)
  XBGAS_DECL_PUT_SIGNAL(long, long)
  XBGAS_DECL_PUT_SIGNAL(long long, longlong)
  XBGAS_DECL_PUT_SIGNAL(unsigned char, uchar)
  XBGAS_DECL_PUT_SIGNAL(unsigned short, ushort)
  XBGAS_DECL_PUT_SIGNAL(unsigned int, uint)
  XBGAS_DECL_PUT_SIGNAL(unsigned long, ulong)
  XBGAS_DECL_PUT_SIGNAL(unsigned long long, ulonglong)
  XBGAS_DECL_PUT_SIGNAL(int8_t, int8)
  XBGAS_DECL_PUT_SIGNAL(int16_t, int16)
  XBGAS_DECL_PUT_SIGNAL(int32_t, int32)
  XBGAS_DECL_PUT_SIGNAL(int64_t, int64)
  XBGAS_DECL_PUT_SIGNAL(uint8_t, uint8)
  XBGAS_DECL_PUT_SIGNAL(uint16_t, uint16)
  XBGAS_DECL_PUT_SIGNAL(uint32_t, uint32)
  XBGAS_DECL_PUT_SIGNAL(uint64_t, uint64)
  XBGAS_DECL_PUT_SIGNAL(size_t, size)
  XBGAS_DECL_PUT_SIGNAL(ptrdiff_t, ptrdiff)

#undef XBGAS_DECL_PUT_SIGNAL

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _XBRTIME_TYPES_H_ */

/* EOF */
