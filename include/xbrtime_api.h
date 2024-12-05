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
#include <stdbool.h>

/**
 * xbrtime_TYPE_MEMOP(TYPE *dest, TYPE value, int pe)
 *
 */

#define XBGAS_DECL_P(_type, _typename)                         \
  /**                                                          \
   * @see xbrtime_TYPE_p                                       \
   */                                                          \
  void xbrtime_##_typename##_p(_type *dest,                    \
                               _type value,                    \
                               int pe);                    

  /* P operation */
  XBGAS_DECL_P(float, float)
  XBGAS_DECL_P(double, double)
  XBGAS_DECL_P(long double, longdouble)
  XBGAS_DECL_P(char, char)
  XBGAS_DECL_P(signed char, schar)
  XBGAS_DECL_P(short, short)
  XBGAS_DECL_P(int, int)
  XBGAS_DECL_P(long, long)
  XBGAS_DECL_P(long long, longlong)
  XBGAS_DECL_P(unsigned char, uchar)
  XBGAS_DECL_P(unsigned short, ushort)
  XBGAS_DECL_P(unsigned int, uint)
  XBGAS_DECL_P(unsigned long, ulong)
  XBGAS_DECL_P(unsigned long long, ulonglong)
  XBGAS_DECL_P(int8_t, int8)
  XBGAS_DECL_P(int16_t, int16)
  XBGAS_DECL_P(int32_t, int32)
  XBGAS_DECL_P(int64_t, int64)
  XBGAS_DECL_P(uint8_t, uint8)
  XBGAS_DECL_P(uint16_t, uint16)
  XBGAS_DECL_P(uint32_t, uint32)
  XBGAS_DECL_P(uint64_t, uint64)
  XBGAS_DECL_P(size_t, size)
  XBGAS_DECL_P(ptrdiff_t, ptrdiff)

#undef XBGAS_DECL_P

#define XBGAS_DECL_G(_type, _typename)                               \
  /**                                                                \
   * @see xbrtime_TYPE_g                                             \
   */                                                                \
  _type xbrtime_##_typename##_g(const _type *source,                 \
                                int pe);                    

  /* G operation */
  XBGAS_DECL_G(float, float)
  XBGAS_DECL_G(double, double)
  XBGAS_DECL_G(long double, longdouble)
  XBGAS_DECL_G(char, char)
  XBGAS_DECL_G(signed char, schar)
  XBGAS_DECL_G(short, short)
  XBGAS_DECL_G(int, int)
  XBGAS_DECL_G(long, long)
  XBGAS_DECL_G(long long, longlong)
  XBGAS_DECL_G(unsigned char, uchar)
  XBGAS_DECL_G(unsigned short, ushort)
  XBGAS_DECL_G(unsigned int, uint)
  XBGAS_DECL_G(unsigned long, ulong)
  XBGAS_DECL_G(unsigned long long, ulonglong)
  XBGAS_DECL_G(int8_t, int8)
  XBGAS_DECL_G(int16_t, int16)
  XBGAS_DECL_G(int32_t, int32)
  XBGAS_DECL_G(int64_t, int64)
  XBGAS_DECL_G(uint8_t, uint8)
  XBGAS_DECL_G(uint16_t, uint16)
  XBGAS_DECL_G(uint32_t, uint32)
  XBGAS_DECL_G(uint64_t, uint64)
  XBGAS_DECL_G(size_t, size)
  XBGAS_DECL_G(ptrdiff_t, ptrdiff)

#undef XBGAS_DECL_G

/**
 * xbrtime_TYPE_MEMOP(TYPE *dest, TYPE *source, size_t nelems, int pe)
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
 * xbrtime_TYPE_MEMOP_SIZE(TYPE *dest, TYPE *source, size_t nelems, int pe)
 *
 */

#define XBGAS_DECL_PUTGET_SIZE(_size, _op)                     \
  /**                                                          \
   * @see xbrtime_TYPE_OP                                      \
   */                                                          \
  void xbrtime_##_op##_size(void *dest,                        \
                            const void *source,                \
                            size_t nelems,                     \
                            int pe);                           \
                                                               \
  /**                                                          \
   * @see xbrtime_TYPE_OP_NBI                                  \
   */                                                          \
  void xbrtime_##_op##_size##_nbi(void *dest,                  \
                                  const void *source,          \
                                  size_t nelems,               \
                                  int pe);

  /* Put operation */
  XBGAS_DECL_PUTGET_SIZE(8, put)
  XBGAS_DECL_PUTGET_SIZE(16, put)
  XBGAS_DECL_PUTGET_SIZE(32, put)
  XBGAS_DECL_PUTGET_SIZE(64, put)
  XBGAS_DECL_PUTGET_SIZE(128, put)

  /* Get operation */
  XBGAS_DECL_PUTGET_SIZE(8, get)
  XBGAS_DECL_PUTGET_SIZE(16, get)
  XBGAS_DECL_PUTGET_SIZE(32, get)
  XBGAS_DECL_PUTGET_SIZE(64, get)
  XBGAS_DECL_PUTGET_SIZE(128, get)

#undef XBGAS_DECL_PUTGET_SIZE

void xbrtime_putmem(void *dest, const void *source, size_t nelems, int pe);
void xbrtime_putmem_nbi(void *dest, const void *source, size_t nelems, int pe);
void xbrtime_getmem(void *dest, const void *source, size_t nelems, int pe); 
void xbrtime_getmem_nbi(void *dest, const void *source, size_t nelems, int pe);

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

/**
 * xbrtime_TYPE_MEMOP(TYPE *dest, TYPE *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe)
 *
 */

#define XBGAS_DECL_PUT_SIGNAL(_type, _typename)             \
  /**                                                       \
   * @see xbrtime_TYPE_PUT_SIGNAL                           \
   */                                                       \
  void xbrtime_##_typename##_put_signal(_type *dest,        \
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
  void xbrtime_##_typename##_put_signal_nbi(_type *dest,    \
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


/* Signal Fetch */
uint64_t xbrtime_signal_fetch(const uint64_t *sig_addr);

#endif /* _XBRTIME_API_H_ */

/* EOF */
