/*
 * _XBRTIME_API_C_
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

#define _PUT_DEBUG_

/* ------------------------------------------------- FUNCTION PROTOTYPES */
void __xbrtime_asm_fence();
void __xbrtime_asm_quiet_fence();

uint32_t xbrtime_decode_pe( int pe );
uint64_t __xbrtime_ltor(uint64_t remote,int pe);

void __xbrtime_put_1( uint64_t dest, uint64_t value, uint32_t pe );
void __xbrtime_put_2( uint64_t dest, uint64_t value, uint32_t pe );
void __xbrtime_put_4( uint64_t dest, uint64_t value, uint32_t pe );
void __xbrtime_put_8( uint64_t dest, uint64_t value, uint32_t pe );
void __xbrtime_put_f4( uint64_t dest, uint64_t value, uint32_t pe );
void __xbrtime_put_f8( uint64_t dest, uint64_t value, uint32_t pe );

uint64_t __xbrtime_get_u1( uint64_t source, uint32_t pe );
uint64_t __xbrtime_get_s1( uint64_t source, uint32_t pe );
uint64_t __xbrtime_get_u2( uint64_t source, uint32_t pe );
uint64_t __xbrtime_get_s2( uint64_t source, uint32_t pe );
float __xbrtime_get_f4( uint64_t source, uint32_t pe );
double __xbrtime_get_f8( uint64_t source, uint32_t pe );
uint64_t __xbrtime_get_4( uint64_t source, uint32_t pe );
uint64_t __xbrtime_get_8( uint64_t source, uint32_t pe );

void __xbrtime_put_1_agg( uint64_t dest, uint64_t source, uint32_t nelems, uint32_t pe );
void __xbrtime_put_2_agg( uint64_t dest, uint64_t source, uint32_t nelems, uint32_t pe );
void __xbrtime_put_4_agg( uint64_t dest, uint64_t source, uint32_t nelems, uint32_t pe );
void __xbrtime_put_8_agg( uint64_t dest, uint64_t source, uint32_t nelems, uint32_t pe );

void __xbrtime_put_1_agg_nbi( uint64_t dest, uint64_t source, uint32_t nelems, uint32_t pe );
void __xbrtime_put_2_agg_nbi( uint64_t dest, uint64_t source, uint32_t nelems, uint32_t pe );
void __xbrtime_put_4_agg_nbi( uint64_t dest, uint64_t source, uint32_t nelems, uint32_t pe );
void __xbrtime_put_8_agg_nbi( uint64_t dest, uint64_t source, uint32_t nelems, uint32_t pe );

void __xbrtime_get_1_agg( uint64_t dest, uint64_t source, uint32_t nelems, uint32_t pe );
void __xbrtime_get_2_agg( uint64_t dest, uint64_t source, uint32_t nelems, uint32_t pe );
void __xbrtime_get_4_agg( uint64_t dest, uint64_t source, uint32_t nelems, uint32_t pe );
void __xbrtime_get_8_agg( uint64_t dest, uint64_t source, uint32_t nelems, uint32_t pe );

void __xbrtime_get_1_agg_nbi( uint64_t dest, uint64_t source, uint32_t nelems, uint32_t pe );
void __xbrtime_get_2_agg_nbi( uint64_t dest, uint64_t source, uint32_t nelems, uint32_t pe );
void __xbrtime_get_4_agg_nbi( uint64_t dest, uint64_t source, uint32_t nelems, uint32_t pe );
void __xbrtime_get_8_agg_nbi( uint64_t dest, uint64_t source, uint32_t nelems, uint32_t pe );

void __xbrtime_put_u1_seq( uint64_t dest, uint64_t source, uint64_t d_stride, uint64_t s_stride, uint32_t nelems, uint32_t pe );
void __xbrtime_put_s1_seq( uint64_t dest, uint64_t source, uint64_t d_stride, uint64_t s_stride, uint32_t nelems, uint32_t pe );
void __xbrtime_put_u2_seq( uint64_t dest, uint64_t source, uint64_t d_stride, uint64_t s_stride, uint32_t nelems, uint32_t pe );
void __xbrtime_put_s2_seq( uint64_t dest, uint64_t source, uint64_t d_stride, uint64_t s_stride, uint32_t nelems, uint32_t pe );
void __xbrtime_put_4_seq( uint64_t dest, uint64_t source, uint64_t d_stride, uint64_t s_stride, uint32_t nelems, uint32_t pe );
void __xbrtime_put_8_seq( uint64_t dest, uint64_t source, uint64_t d_stride, uint64_t s_stride, uint32_t nelems, uint32_t pe );

void __xbrtime_get_u1_seq( uint64_t dest, uint64_t source, uint64_t d_stride, uint64_t s_stride, uint32_t nelems, uint32_t pe );
void __xbrtime_get_s1_seq( uint64_t dest, uint64_t source, uint64_t d_stride, uint64_t s_stride, uint32_t nelems, uint32_t pe );
void __xbrtime_get_u2_seq( uint64_t dest, uint64_t source, uint64_t d_stride, uint64_t s_stride, uint32_t nelems, uint32_t pe );
void __xbrtime_get_s2_seq( uint64_t dest, uint64_t source, uint64_t d_stride, uint64_t s_stride, uint32_t nelems, uint32_t pe );
void __xbrtime_get_4_seq( uint64_t dest, uint64_t source, uint64_t d_stride, uint64_t s_stride, uint32_t nelems, uint32_t pe );
void __xbrtime_get_8_seq( uint64_t dest, uint64_t source, uint64_t d_stride, uint64_t s_stride, uint32_t nelems, uint32_t pe );

#define XBGAS_P(_type, _typename, _typesize )                                               \
void xbrtime_##_typename##_p(_type *dest, _type value, int pe)                              \
{                                                                                           \
  return __xbrtime_put_##_typesize(__xbrtime_ltor((uint64_t)(dest),pe),                     \
                                  (_type)(value),                                           \
                                  xbrtime_decode_pe(pe));                                   \
}                                                                                                   

  XBGAS_P(float, float, f4)
  XBGAS_P(double, double, f8)
  XBGAS_P(long double, longdouble, 8)
  XBGAS_P(char, char, 1)
  XBGAS_P(signed char, schar, 1)
  XBGAS_P(short, short, 2)
  XBGAS_P(int, int, 4)
  XBGAS_P(long, long, 8)
  XBGAS_P(long long, longlong, 8)
  XBGAS_P(unsigned char, uchar, 1)
  XBGAS_P(unsigned short, ushort, 2)
  XBGAS_P(unsigned int, uint, 4)
  XBGAS_P(unsigned long, ulong, 8)
  XBGAS_P(unsigned long long, ulonglong, 8)
  XBGAS_P(int8_t, int8, 1)
  XBGAS_P(int16_t, int16, 2)
  XBGAS_P(int32_t, int32, 4)
  XBGAS_P(int64_t, int64, 8)
  XBGAS_P(uint8_t, uint8, 1)
  XBGAS_P(uint16_t, uint16, 2)
  XBGAS_P(uint32_t, uint32, 4)
  XBGAS_P(uint64_t, uint64, 8)
  XBGAS_P(size_t, size, 4)
  XBGAS_P(ptrdiff_t, ptrdiff, 8)

#undef XBGAS_P

#define XBGAS_G(_type, _typename, _typesize )                                                                           \
_type xbrtime_##_typename##_g(const _type *source, int pe)                                                              \
{                                                                                                                       \
                                                                                                                        \
    return ((_type)__xbrtime_get_##_typesize(__xbrtime_ltor((uint64_t)(source), pe),                                    \
                                             xbrtime_decode_pe(pe)));                                                   \
}                                                                                                   

  XBGAS_G(float, float, f4)
  XBGAS_G(double, double, f8)
  XBGAS_G(long double, longdouble, 8)
  XBGAS_G(char, char, u1)
  XBGAS_G(signed char, schar, s1)
  XBGAS_G(short, short, s2)
  XBGAS_G(int, int, 4)
  XBGAS_G(long, long, 8)
  XBGAS_G(long long, longlong, 8)
  XBGAS_G(unsigned char, uchar, u1)
  XBGAS_G(unsigned short, ushort, u2)
  XBGAS_G(unsigned int, uint, 4)
  XBGAS_G(unsigned long, ulong, 8)
  XBGAS_G(unsigned long long, ulonglong, 8)
  XBGAS_G(int8_t, int8, s1)
  XBGAS_G(int16_t, int16, s2)
  XBGAS_G(int32_t, int32, 4)
  XBGAS_G(int64_t, int64, 8)
  XBGAS_G(uint8_t, uint8, u1)
  XBGAS_G(uint16_t, uint16, u2)
  XBGAS_G(uint32_t, uint32, 4)
  XBGAS_G(uint64_t, uint64, 8)
  XBGAS_G(size_t, size, 4)
  XBGAS_G(ptrdiff_t, ptrdiff, 8)

#undef XBGAS_G

#define XBGAS_PUT(_type, _typename, _typesize )                                                     \
void xbrtime_##_typename##_put(_type *dest, const _type *source, size_t nelems, int pe)             \
{                                                                                                   \
  if(nelems == 0){                                                                                  \
    return;                                                                                         \
  }else{                                                                                            \
    return __xbrtime_put_##_typesize##_agg(__xbrtime_ltor((uint64_t)(dest),pe),                     \
                                          (uint64_t)(source),                                       \
                                          (uint32_t)(nelems),                                       \
                                          xbrtime_decode_pe(pe));                                   \
  }                                                                                                 \
}                                                                                                   \
                                                                                                    \
void xbrtime_##_typename##_put_nbi(_type *dest, const _type *source, size_t nelems, int pe)         \
{                                                                                                   \
  if(nelems == 0){                                                                                  \
    return;                                                                                         \
  }else{                                                                                            \
    return __xbrtime_put_##_typesize##_agg_nbi(__xbrtime_ltor((uint64_t)(dest),pe),                 \
                                              (uint64_t)(source),                                   \
                                              (uint32_t)(nelems),                                   \
                                              xbrtime_decode_pe(pe));                               \
  }                                                                                                 \
}   


  XBGAS_PUT(float, float, 4)
  XBGAS_PUT(double, double, 8)
  XBGAS_PUT(long double, longdouble, 8)
  XBGAS_PUT(char, char, 1)
  XBGAS_PUT(signed char, schar, 1)
  XBGAS_PUT(short, short, 2)
  XBGAS_PUT(int, int, 4)
  XBGAS_PUT(long, long, 8)
  XBGAS_PUT(long long, longlong, 8)
  XBGAS_PUT(unsigned char, uchar, 1)
  XBGAS_PUT(unsigned short, ushort, 2)
  XBGAS_PUT(unsigned int, uint, 4)
  XBGAS_PUT(unsigned long, ulong, 8)
  XBGAS_PUT(unsigned long long, ulonglong, 8)
  XBGAS_PUT(int8_t, int8, 1)
  XBGAS_PUT(int16_t, int16, 2)
  XBGAS_PUT(int32_t, int32, 4)
  XBGAS_PUT(int64_t, int64, 8)
  XBGAS_PUT(uint8_t, uint8, 1)
  XBGAS_PUT(uint16_t, uint16, 2)
  XBGAS_PUT(uint32_t, uint32, 4)
  XBGAS_PUT(uint64_t, uint64, 8)
  XBGAS_PUT(size_t, size, 4)
  XBGAS_PUT(ptrdiff_t, ptrdiff, 8)

#undef XBGAS_PUT

#define XBGAS_PUT_SIZE( _size )                                                                     \
void xbrtime_put##_size(void *dest, const void *source, size_t nelems, int pe)                      \
{                                                                                                   \
  if(nelems == 0){                                                                                  \
    return;                                                                                         \
  }else{                                                                                            \
    size_t total_nelems = nelems * _size;                                                           \
    return __xbrtime_put_1_agg(__xbrtime_ltor((uint64_t)(dest),pe),                                 \
                                          (uint64_t)(source),                                       \
                                          (uint32_t)(total_nelems),                                 \
                                          xbrtime_decode_pe(pe));                                   \
  }                                                                                                 \
}                                                                                                   \
                                                                                                    \
void xbrtime_put##_size##_nbi(void *dest, const void *source, size_t nelems, int pe)                \
{                                                                                                   \
  if(nelems == 0){                                                                                  \
    return;                                                                                         \
  }else{                                                                                            \
    size_t total_nelems = nelems * _size;                                                           \
    return __xbrtime_put_1_agg_nbi(__xbrtime_ltor((uint64_t)(dest),pe),                             \
                                              (uint64_t)(source),                                   \
                                              (uint32_t)(total_nelems),                             \
                                              xbrtime_decode_pe(pe));                               \
  }                                                                                                 \
}
  XBGAS_PUT_SIZE(8)
  XBGAS_PUT_SIZE(16)
  XBGAS_PUT_SIZE(32)
  XBGAS_PUT_SIZE(64)
  XBGAS_PUT_SIZE(128)

#undef XBGAS_PUT_SIZE

void xbrtime_putmem(void *dest, const void *source, size_t nelems, int pe)
{
  if(nelems == 0){
    return;
  }else{
    return __xbrtime_put_1_agg(__xbrtime_ltor((uint64_t)(dest),pe),
                               (uint64_t)(source),
                               (uint32_t)(nelems),
                               xbrtime_decode_pe(pe));
  }
}

void xbrtime_putmem_nbi(void *dest, const void *source, size_t nelems, int pe)
{
  if(nelems == 0){
    return;
  }else{
    return __xbrtime_put_1_agg_nbi(__xbrtime_ltor((uint64_t)(dest),pe),
                                   (uint64_t)(source),
                                   (uint32_t)(nelems),
                                   xbrtime_decode_pe(pe));
  }
}

#define XBGAS_GET(_type, _typename, _typesize )                                                     \
void xbrtime_##_typename##_get(_type *dest, const _type *source, size_t nelems, int pe)             \
{                                                                                                   \
  if(nelems == 0){                                                                                  \
    return;                                                                                         \
  }else{                                                                                            \
    return __xbrtime_get_##_typesize##_agg((uint64_t)(dest),                                        \
                                           __xbrtime_ltor((uint64_t)(source), pe),                  \
                                           (uint32_t)(nelems),                                      \
                                           xbrtime_decode_pe(pe));                                  \
  }                                                                                                 \
}                                                                                                   \
                                                                                                    \
void xbrtime_##_typename##_get_nbi(_type *dest, const _type *source, size_t nelems, int pe)         \
{                                                                                                   \
  if(nelems == 0){                                                                                  \
    return;                                                                                         \
  }else{                                                                                            \
    return __xbrtime_get_##_typesize##_agg_nbi((uint64_t)(dest),                                    \
                                                __xbrtime_ltor((uint64_t)(source), pe),             \
                                                (uint32_t)(nelems),                                 \
                                                xbrtime_decode_pe(pe));                             \
  }                                                                                                 \
} 

  /* Get operation */
  XBGAS_GET(float, float, 4)
  XBGAS_GET(double, double, 8)
  XBGAS_GET(long double, longdouble, 8)
  XBGAS_GET(char, char, 1)
  XBGAS_GET(signed char, schar, 1)
  XBGAS_GET(short, short, 2)
  XBGAS_GET(int, int, 4)
  XBGAS_GET(long, long, 8)
  XBGAS_GET(long long, longlong, 8)
  XBGAS_GET(unsigned char, uchar, 1)
  XBGAS_GET(unsigned short, ushort, 2)
  XBGAS_GET(unsigned int, uint, 4)
  XBGAS_GET(unsigned long, ulong, 8)
  XBGAS_GET(unsigned long long, ulonglong, 8)
  XBGAS_GET(int8_t, int8, 1)
  XBGAS_GET(int16_t, int16, 2)
  XBGAS_GET(int32_t, int32, 4)
  XBGAS_GET(int64_t, int64, 8)
  XBGAS_GET(uint8_t, uint8, 1)
  XBGAS_GET(uint16_t, uint16, 2)
  XBGAS_GET(uint32_t, uint32, 4)
  XBGAS_GET(uint64_t, uint64, 8)
  XBGAS_GET(size_t, size, 4)
  XBGAS_GET(ptrdiff_t, ptrdiff, 8)

#undef XBGAS_GET

#define XBGAS_GET_SIZE( _size )                                                                     \
void xbrtime_get##_size(void *dest, const void *source, size_t nelems, int pe)                      \
{                                                                                                   \
  if(nelems == 0){                                                                                  \
    return;                                                                                         \
  }else{                                                                                            \
    size_t total_nelems = nelems * _size;                                                           \
    return __xbrtime_get_1_agg((uint64_t)(dest),                                                    \
                               __xbrtime_ltor((uint64_t)(source), pe),                              \
                               (uint32_t)(total_nelems),                                            \
                               xbrtime_decode_pe(pe));                                              \
  }                                                                                                 \
}                                                                                                   \
                                                                                                    \
void xbrtime_get##_size##_nbi(void *dest, const void *source, size_t nelems, int pe)                \
{                                                                                                   \
  if(nelems == 0){                                                                                  \
    return;                                                                                         \
  }else{                                                                                            \
    size_t total_nelems = nelems * _size;                                                           \
    return __xbrtime_get_1_agg_nbi((uint64_t)(dest),                                                \
                                   __xbrtime_ltor((uint64_t)(source), pe),                          \
                                   (uint32_t)(total_nelems),                                        \
                                   xbrtime_decode_pe(pe));                                          \
  }                                                                                                 \
}
  XBGAS_GET_SIZE(8)
  XBGAS_GET_SIZE(16)
  XBGAS_GET_SIZE(32)
  XBGAS_GET_SIZE(64)
  XBGAS_GET_SIZE(128)

#undef XBGAS_GET_SIZE

void xbrtime_getmem(void *dest, const void *source, size_t nelems, int pe)
{
  if(nelems == 0){
    return;
  }else{
    return __xbrtime_get_1_agg((uint64_t)(dest),
                               __xbrtime_ltor((uint64_t)(source), pe),
                               (uint32_t)(nelems),
                               xbrtime_decode_pe(pe));
  }
}

void xbrtime_getmem_nbi(void *dest, const void *source, size_t nelems, int pe)
{
  if(nelems == 0){
    return;
  }else{
    return __xbrtime_get_1_agg_nbi((uint64_t)(dest),
                                   __xbrtime_ltor((uint64_t)(source), pe),
                                   (uint32_t)(nelems),
                                   xbrtime_decode_pe(pe));
  }
}

#define XBGAS_I_PUT(_type, _typename, _typesize )                                                                       \
void xbrtime_##_typename##_iput(_type *dest, const _type *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems, int pe)  \
{                                                                                                                       \
  if(nelems == 0){                                                                                                      \
    return;                                                                                                             \
  }else{                                                                                                                \
    uint64_t d_stride = (uint64_t)(dst * sizeof(_type) );                                                               \
    uint64_t s_stride = (uint64_t)(sst * sizeof(_type) );                                                               \
    return __xbrtime_put_##_typesize##_seq(__xbrtime_ltor((uint64_t)(dest),pe),                                         \
                                          (uint64_t)(source),                                                           \
                                          d_stride,                                                                     \
                                          s_stride,                                                                     \
                                          (uint32_t)(nelems),                                                           \
                                          xbrtime_decode_pe(pe));                                                       \
  }                                                                                                                     \
}                                                                                                   
                                                                                                    
  /* Strided-Put operation */
  XBGAS_I_PUT(float, float, 4)
  XBGAS_I_PUT(double, double, 8)
  XBGAS_I_PUT(long double, longdouble, 8)
  XBGAS_I_PUT(char, char, u1)
  XBGAS_I_PUT(signed char, schar, s1)
  XBGAS_I_PUT(short, short, s2)
  XBGAS_I_PUT(int, int, 4)
  XBGAS_I_PUT(long, long, 8)
  XBGAS_I_PUT(long long, longlong, 8)
  XBGAS_I_PUT(unsigned char, uchar, u1)
  XBGAS_I_PUT(unsigned short, ushort, u2)
  XBGAS_I_PUT(unsigned int, uint, 4)
  XBGAS_I_PUT(unsigned long, ulong, 8)
  XBGAS_I_PUT(unsigned long long, ulonglong, 8)
  XBGAS_I_PUT(int8_t, int8, s1)
  XBGAS_I_PUT(int16_t, int16, s2)
  XBGAS_I_PUT(int32_t, int32, 4)
  XBGAS_I_PUT(int64_t, int64, 8)
  XBGAS_I_PUT(uint8_t, uint8, u1)
  XBGAS_I_PUT(uint16_t, uint16, u2)
  XBGAS_I_PUT(uint32_t, uint32, 4)
  XBGAS_I_PUT(uint64_t, uint64, 8)
  XBGAS_I_PUT(size_t, size, 4)
  XBGAS_I_PUT(ptrdiff_t, ptrdiff, 8)

#undef XBGAS_I_PUT

#define XBGAS_I_GET(_type, _typename, _typesize )                                                                       \
void xbrtime_##_typename##_iget(_type *dest, const _type *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems, int pe)  \
{                                                                                                                       \
  if(nelems == 0){                                                                                                      \
    return;                                                                                                             \
  }else{                                                                                                                \
    uint64_t d_stride = (uint64_t)(dst * sizeof(_type) );                                                               \
    uint64_t s_stride = (uint64_t)(sst * sizeof(_type) );                                                               \
    __xbrtime_get_##_typesize##_seq((uint64_t)(dest),                                                                   \
                                    __xbrtime_ltor((uint64_t)(source), pe),                                             \
                                    d_stride,                                                                           \
                                    s_stride,                                                                           \
                                    (uint32_t)(nelems),                                                                 \
                                    xbrtime_decode_pe(pe));                                                             \
    __xbrtime_asm_fence();                                                                                              \
    return;                                                                                                             \
  }                                                                                                                     \
}

  /* Strided-Get operation */
  XBGAS_I_GET(float, float, 4)
  XBGAS_I_GET(double, double, 8)
  XBGAS_I_GET(long double, longdouble, 8)
  XBGAS_I_GET(char, char, u1)
  XBGAS_I_GET(signed char, schar, s1)
  XBGAS_I_GET(short, short, s2)
  XBGAS_I_GET(int, int, 4)
  XBGAS_I_GET(long, long, 8)
  XBGAS_I_GET(long long, longlong, 8)
  XBGAS_I_GET(unsigned char, uchar, u1)
  XBGAS_I_GET(unsigned short, ushort, u2)
  XBGAS_I_GET(unsigned int, uint, 4)
  XBGAS_I_GET(unsigned long, ulong, 8)
  XBGAS_I_GET(unsigned long long, ulonglong, 8)
  XBGAS_I_GET(int8_t, int8, s1)
  XBGAS_I_GET(int16_t, int16, s2)
  XBGAS_I_GET(int32_t, int32, 4)
  XBGAS_I_GET(int64_t, int64, 8)
  XBGAS_I_GET(uint8_t, uint8, u1)
  XBGAS_I_GET(uint16_t, uint16, u2)
  XBGAS_I_GET(uint32_t, uint32, 4)
  XBGAS_I_GET(uint64_t, uint64, 8)
  XBGAS_I_GET(size_t, size, 4)
  XBGAS_I_GET(ptrdiff_t, ptrdiff, 8)

#undef XBGAS_I_GET

#define XBGAS_PUT_SIGNAL(_type, _typename, _typesize)                                         \
void xbrtime_##_typename##_put_signal( _type *dest,                                           \
                                      const _type *source,                                    \
                                      size_t nelems,                                          \
                                      uint64_t *sig_addr,                                     \
                                      uint64_t signal,                                        \
                                      int sig_op,                                             \
                                      int pe )                                                \
{                                                                                             \
  __xbrtime_put_##_typesize##_agg(__xbrtime_ltor((uint64_t)(dest),pe),                        \
                                                 (uint64_t)(source),                          \
                                                 (uint32_t)(nelems),                          \
                                                 xbrtime_decode_pe(pe));                      \
  switch ( sig_op ) {                                                                         \
    case XBRTIME_SIGNAL_SET:                                                                  \
      __xbrtime_atomic_set_u8(__xbrtime_ltor((uint64_t)(sig_addr),pe),                        \
                              signal,                                                         \
                              xbrtime_decode_pe(pe));                                         \
      break;                                                                                  \
    case XBRTIME_SIGNAL_ADD:                                                                  \
      __xbrtime_atomic_add_u8(__xbrtime_ltor((uint64_t)(sig_addr),pe),                        \
                              signal,                                                         \
                              xbrtime_decode_pe(pe));                                         \
      break;                                                                                  \
    default:                                                                                  \
      break;                                                                                  \
  }                                                                                           \
  return;                                                                                     \
}

  XBGAS_PUT_SIGNAL(float, float, 4)
  XBGAS_PUT_SIGNAL(double, double, 8)
  XBGAS_PUT_SIGNAL(long double, longdouble, 8)
  XBGAS_PUT_SIGNAL(char, char, 1)
  XBGAS_PUT_SIGNAL(signed char, schar, 1)
  XBGAS_PUT_SIGNAL(short, short, 2)
  XBGAS_PUT_SIGNAL(int, int, 4)
  XBGAS_PUT_SIGNAL(long, long, 8)
  XBGAS_PUT_SIGNAL(long long, longlong, 8)
  XBGAS_PUT_SIGNAL(unsigned char, uchar, 1)
  XBGAS_PUT_SIGNAL(unsigned short, ushort, 2)
  XBGAS_PUT_SIGNAL(unsigned int, uint, 4)
  XBGAS_PUT_SIGNAL(unsigned long, ulong, 8)
  XBGAS_PUT_SIGNAL(unsigned long long, ulonglong, 8)
  XBGAS_PUT_SIGNAL(int8_t, int8, 1)
  XBGAS_PUT_SIGNAL(int16_t, int16, 2)
  XBGAS_PUT_SIGNAL(int32_t, int32, 4)
  XBGAS_PUT_SIGNAL(int64_t, int64, 8)
  XBGAS_PUT_SIGNAL(uint8_t, uint8, 1)
  XBGAS_PUT_SIGNAL(uint16_t, uint16, 2)
  XBGAS_PUT_SIGNAL(uint32_t, uint32, 4)
  XBGAS_PUT_SIGNAL(uint64_t, uint64, 8)
  XBGAS_PUT_SIGNAL(size_t, size, 4)
  XBGAS_PUT_SIGNAL(ptrdiff_t, ptrdiff, 8)

#undef XBGAS_PUT_SIGNAL

#define XBGAS_PUT_SIGNAL_NBI(_type, _typename, _typesize)                            \
void xbrtime_##_typename##_put_signal_nbi( _type *dest,                              \
                                          const _type *source,                       \
                                          size_t nelems,                             \
                                          uint64_t *sig_addr,                        \
                                          uint64_t signal,                           \
                                          int sig_op,                                \
                                          int pe )                                   \
{                                                                                    \
  __xbrtime_put_##_typesize##_agg_nbi(__xbrtime_ltor((uint64_t)(dest),pe),           \
                                     (uint64_t)(source),                             \
                                     (uint32_t)(nelems),                             \
                                      xbrtime_decode_pe(pe));                        \
  switch ( sig_op ) {                                                                \
    case XBRTIME_SIGNAL_SET:                                                         \
      __xbrtime_atomic_set_u8(__xbrtime_ltor((uint64_t)(sig_addr),pe),               \
                              signal,                                                \
                              xbrtime_decode_pe(pe));                                \
      break;                                                                         \
    case XBRTIME_SIGNAL_ADD:                                                         \
      __xbrtime_atomic_add_u8(__xbrtime_ltor((uint64_t)(sig_addr),pe),               \
                              signal,                                                \
                              xbrtime_decode_pe(pe));                                \
      break;                                                                         \
    default:                                                                         \
      break;                                                                         \
  }                                                                                  \
  return;                                                                            \
}

  XBGAS_PUT_SIGNAL_NBI(float, float, 4)
  XBGAS_PUT_SIGNAL_NBI(double, double, 8)
  XBGAS_PUT_SIGNAL_NBI(long double, longdouble, 8)
  XBGAS_PUT_SIGNAL_NBI(char, char, 1)
  XBGAS_PUT_SIGNAL_NBI(signed char, schar, 1)
  XBGAS_PUT_SIGNAL_NBI(short, short, 2)
  XBGAS_PUT_SIGNAL_NBI(int, int, 4)
  XBGAS_PUT_SIGNAL_NBI(long, long, 8)
  XBGAS_PUT_SIGNAL_NBI(long long, longlong, 8)
  XBGAS_PUT_SIGNAL_NBI(unsigned char, uchar, 1)
  XBGAS_PUT_SIGNAL_NBI(unsigned short, ushort, 2)
  XBGAS_PUT_SIGNAL_NBI(unsigned int, uint, 4)
  XBGAS_PUT_SIGNAL_NBI(unsigned long, ulong, 8)
  XBGAS_PUT_SIGNAL_NBI(unsigned long long, ulonglong, 8)
  XBGAS_PUT_SIGNAL_NBI(int8_t, int8, 1)
  XBGAS_PUT_SIGNAL_NBI(int16_t, int16, 2)
  XBGAS_PUT_SIGNAL_NBI(int32_t, int32, 4)
  XBGAS_PUT_SIGNAL_NBI(int64_t, int64, 8)
  XBGAS_PUT_SIGNAL_NBI(uint8_t, uint8, 1)
  XBGAS_PUT_SIGNAL_NBI(uint16_t, uint16, 2)
  XBGAS_PUT_SIGNAL_NBI(uint32_t, uint32, 4)
  XBGAS_PUT_SIGNAL_NBI(uint64_t, uint64, 8)
  XBGAS_PUT_SIGNAL_NBI(size_t, size, 4)
  XBGAS_PUT_SIGNAL_NBI(ptrdiff_t, ptrdiff, 8)

#undef XBGAS_PUT_SIGNAL_NBI

uint64_t xbrtime_signal_fetch(const uint64_t *sig_addr) {
  return __xbrtime_atomic_fetch_8((uint64_t)(sig_addr));
}

/* EOF */
