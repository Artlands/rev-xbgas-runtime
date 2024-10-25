/*
 * _XBRTIME_WAIT_C_
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

#define XBGAS_WAIT_UNTIL(_type, _typename)                                           \
void xbrtime_##_typename##_wait_until(_type *ivar, int cmp, _type cmp_value)         \
{                                                                                    \ 
  while(1){                                                                          \
    if(cmp == XBRTIME_CMP_EQ){                                                       \
      if(*ivar == cmp_value){                                                        \
        break;                                                                       \
      }                                                                              \
    }else if(cmp == XBRTIME_CMP_NE){                                                 \
      if(*ivar != cmp_value){                                                        \
        break;                                                                       \
      }                                                                              \
    }else if(cmp == XBRTIME_CMP_GT){                                                 \
      if(*ivar > cmp_value){                                                         \
        break;                                                                       \
      }                                                                              \
    }else if(cmp == XBRTIME_CMP_LE){                                                 \
      if(*ivar <= cmp_value){                                                        \
        break;                                                                       \
      }                                                                              \
    }else if(cmp == XBRTIME_CMP_LT){                                                 \
      if(*ivar < cmp_value){                                                         \
        break;                                                                       \
      }                                                                              \
    }else if(cmp == XBRTIME_CMP_GE){                                                 \
      if(*ivar >= cmp_value){                                                        \
        break;                                                                       \  
      }                                                                              \
    }                                                                                \
  }                                                                                  \
}

    /* Wait operations */
    XBGAS_WAIT_UNTIL(int, int)
    XBGAS_WAIT_UNTIL(long, long)
    XBGAS_WAIT_UNTIL(long long, longlong)
    XBGAS_WAIT_UNTIL(unsigned int, uint)
    XBGAS_WAIT_UNTIL(unsigned long, ulong)
    XBGAS_WAIT_UNTIL(unsigned long long, ulonglong)
    XBGAS_WAIT_UNTIL(int32_t, int32)
    XBGAS_WAIT_UNTIL(uint64_t, uint64)
    XBGAS_WAIT_UNTIL(uint32_t, uint32)
    XBGAS_WAIT_UNTIL(int64_t, int64)
    XBGAS_WAIT_UNTIL(size_t, size)
    XBGAS_WAIT_UNTIL(ptrdiff_t, ptrdiff)

#undef XBGAS_WAIT_UNTIL

#define XBGAS_WAIT_UNTIL_ALL(_type, _typename)                                                                      \ 
void xbrtime_##_typename##_wait_until_all(_type *ivars, size_t nelems, const int *status, int cmp, _type cmp_value) \
{                                                                                                                   \
  size_t i;                                                                                                         \
  int flag = 0;                                                                                                     \
  while(1){                                                                                                         \
    flag = 0;                                                                                                       \
    for(i=0;i<nelems;++i){                                                                                          \
      if(status[i] == 0){                                                                                           \
        if(cmp == XBRTIME_CMP_EQ){                                                                                  \
          if(ivars[i] != cmp_value){                                                                                \
            flag = 1;                                                                                               \
            break;                                                                                                  \
          }                                                                                                         \
        }else if(cmp == XBRTIME_CMP_NE){                                                                            \  
          if(ivars[i] == cmp_value){                                                                                \
            flag = 1;                                                                                               \
            break;                                                                                                  \
          }                                                                                                         \
        }else if(cmp == XBRTIME_CMP_GT){                                                                            \
          if(ivars[i] <= cmp_value){                                                                                \
            flag = 1;                                                                                               \
            break;                                                                                                  \
          }                                                                                                         \
        }else if(cmp == XBRTIME_CMP_LE){                                                                            \
          if(ivars[i] > cmp_value){                                                                                 \
            flag = 1;                                                                                               \
            break;                                                                                                  \
          }                                                                                                         \
        }else if(cmp == XBRTIME_CMP_LT){                                                                            \
          if(ivars[i] >= cmp_value){                                                                                \
            flag = 1;                                                                                               \
            break;                                                                                                  \
          }                                                                                                         \
        }else if(cmp == XBRTIME_CMP_GE){                                                                            \
          if(ivars[i] < cmp_value){                                                                                 \
            flag = 1;                                                                                               \
            break;                                                                                                  \
          }                                                                                                         \
        }                                                                                                           \
      }                                                                                                             \
    }                                                                                                               \
    if(flag == 0){                                                                                                  \
      break;                                                                                                        \
    }                                                                                                               \
  }                                                                                                                 \
}

    /* Wait until all operations */
    XBGAS_WAIT_UNTIL_ALL(int, int)
    XBGAS_WAIT_UNTIL_ALL(long, long)
    XBGAS_WAIT_UNTIL_ALL(long long, longlong)
    XBGAS_WAIT_UNTIL_ALL(unsigned int, uint)
    XBGAS_WAIT_UNTIL_ALL(unsigned long, ulong)
    XBGAS_WAIT_UNTIL_ALL(unsigned long long, ulonglong)
    XBGAS_WAIT_UNTIL_ALL(int32_t, int32)
    XBGAS_WAIT_UNTIL_ALL(uint64_t, uint64)
    XBGAS_WAIT_UNTIL_ALL(uint32_t, uint32)
    XBGAS_WAIT_UNTIL_ALL(int64_t, int64)
    XBGAS_WAIT_UNTIL_ALL(size_t, size)
    XBGAS_WAIT_UNTIL_ALL(ptrdiff_t, ptrdiff)

#undef XBGAS_WAIT_UNTIL_ALL

#define XBGAS_WAIT_UNTIL_ANY(_type, _typename)                                                                          \ 
size_t xbrtime_##_typename##_wait_until_any(_type *ivars, size_t nelems, const int *status, int cmp, _type cmp_value)   \
{                                                                                                                 \
  size_t i;                                                                                                       \
  int flag = 0;                                                                                                   \
  while(1){                                                                                                       \
    flag = 0;                                                                                                     \
    for(i=0;i<nelems;++i){                                                                                        \
      if(status[i] == 0){                                                                                         \
        if(cmp == XBRTIME_CMP_EQ){                                                                                \
          if(ivars[i] == cmp_value){                                                                              \
            return i;                                                                                             \
          }                                                                                                       \
        }else if(cmp == XBRTIME_CMP_NE){                                                                          \
          if(ivars[i] != cmp_value){                                                                              \
            return i;                                                                                             \
          }                                                                                                       \
        }else if(cmp == XBRTIME_CMP_GT){                                                                          \
          if(ivars[i] > cmp_value){                                                                               \
            return i;                                                                                             \
          }                                                                                                       \
        }else if(cmp == XBRTIME_CMP_LE){                                                                          \
          if(ivars[i] <= cmp_value){                                                                              \
            return i;                                                                                             \
          }                                                                                                       \
        }else if(cmp == XBRTIME_CMP_LT){                                                                          \  
          if(ivars[i] < cmp_value){                                                                               \
            return i;                                                                                             \
          }                                                                                                       \
        }else if(cmp == XBRTIME_CMP_GE){                                                                          \
          if(ivars[i] >= cmp_value){                                                                              \
            return i;                                                                                             \
          }                                                                                                       \
        }                                                                                                         \
      }                                                                                                           \
    }                                                                                                             \
  }                                                                                                               \
}                                                                                                                

    /* Wait any operations */
    XBGAS_WAIT_UNTIL_ANY(int, int)
    XBGAS_WAIT_UNTIL_ANY(long, long)
    XBGAS_WAIT_UNTIL_ANY(long long, longlong)
    XBGAS_WAIT_UNTIL_ANY(unsigned int, uint)
    XBGAS_WAIT_UNTIL_ANY(unsigned long, ulong)
    XBGAS_WAIT_UNTIL_ANY(unsigned long long, ulonglong)
    XBGAS_WAIT_UNTIL_ANY(int32_t, int32)
    XBGAS_WAIT_UNTIL_ANY(uint64_t, uint64)
    XBGAS_WAIT_UNTIL_ANY(uint32_t, uint32)
    XBGAS_WAIT_UNTIL_ANY(int64_t, int64)
    XBGAS_WAIT_UNTIL_ANY(size_t, size)
    XBGAS_WAIT_UNTIL_ANY(ptrdiff_t, ptrdiff)

#undef XBGAS_WAIT_UNTIL_ANY

#define XBGAS_WAIT_UNTIL_SOME(_type, _typename)                                                                                           \ 
size_t xbrtime_##_typename##_wait_until_some(_type *ivars, size_t nelems, size_t *indices, const int *status, int cmp, _type cmp_value)   \ 
{                                                                                                                                   \
  size_t i;                                                                                                                         \
  size_t j = 0;                                                                                                                     \
  int flag = 0;                                                                                                                     \
  while(1){                                                                                                                         \
    flag = 0;                                                                                                                       \
    for(i=0;i<nelems;++i){                                                                                                          \
      if(status[i] == 0){                                                                                                           \
        if(cmp == XBRTIME_CMP_EQ){                                                                                                  \
          if(ivars[i] == cmp_value){                                                                                                \
            indices[j] = i;                                                                                                         \
            j++;                                                                                                                    \
            flag = 1;                                                                                                               \
          }                                                                                                                         \
        }else if(cmp == XBRTIME_CMP_NE){                                                                                            \
          if(ivars[i] != cmp_value){                                                                                                \
            indices[j] = i;                                                                                                         \ 
            j++;                                                                                                                    \
            flag = 1;                                                                                                               \
          }                                                                                                                         \
        }else if(cmp == XBRTIME_CMP_GT){                                                                                            \
          if(ivars[i] > cmp_value){                                                                                                 \
            indices[j] = i;                                                                                                         \
            j++;                                                                                                                    \
            flag = 1;                                                                                                               \
          }                                                                                                                         \
        }else if(cmp == XBRTIME_CMP_LE){                                                                                            \
          if(ivars[i] <= cmp_value){                                                                                                \
            indices[j] = i;                                                                                                         \
            j++;                                                                                                                    \
            flag = 1;                                                                                                               \
          }                                                                                                                         \
        }else if(cmp == XBRTIME_CMP_LT){                                                                                            \
          if(ivars[i] < cmp_value){                                                                                                 \
            indices[j] = i;                                                                                                         \
            j++;                                                                                                                    \
            flag = 1;                                                                                                               \
          }                                                                                                                         \
        }else if(cmp == XBRTIME_CMP_GE){                                                                                            \
          if(ivars[i] >= cmp_value){                                                                                                \
            indices[j] = i;                                                                                                         \
            j++;                                                                                                                    \
            flag = 1;                                                                                                               \
          }                                                                                                                         \
        }                                                                                                                           \
      }                                                                                                                             \
    }                                                                                                                               \
    if(flag == 0){                                                                                                                  \
      break;                                                                                                                        \
    }                                                                                                                               \
  }                                                                                                                                 \
  return j;                                                                                                                         \
}

    /* Wait some operations */
    XBGAS_WAIT_UNTIL_SOME(int, int)
    XBGAS_WAIT_UNTIL_SOME(long, long)
    XBGAS_WAIT_UNTIL_SOME(long long, longlong)
    XBGAS_WAIT_UNTIL_SOME(unsigned int, uint)
    XBGAS_WAIT_UNTIL_SOME(unsigned long, ulong)
    XBGAS_WAIT_UNTIL_SOME(unsigned long long, ulonglong)
    XBGAS_WAIT_UNTIL_SOME(int32_t, int32)
    XBGAS_WAIT_UNTIL_SOME(uint64_t, uint64)
    XBGAS_WAIT_UNTIL_SOME(uint32_t, uint32)
    XBGAS_WAIT_UNTIL_SOME(int64_t, int64)
    XBGAS_WAIT_UNTIL_SOME(size_t, size)
    XBGAS_WAIT_UNTIL_SOME(ptrdiff_t, ptrdiff)

#undef XBGAS_WAIT_UNTIL_SOME

#define XBGAS_WAIT_UNTIL_ALL_VECTOR(_type, _typename)                                                                         \ 
void xbrtime_##_typename##_wait_until_all_vector(_type *ivars, size_t nelems, const int *status, int cmp, _type *cmp_values)  \
{                                                                                                                             \
  size_t i;                                                                                                                   \
  int flag = 0;                                                                                                               \
  while(1){                                                                                                                   \
    flag = 0;                                                                                                                 \
    for(i=0;i<nelems;++i){                                                                                                    \
      if(status[i] == 0){                                                                                                     \ 
        if(cmp == XBRTIME_CMP_EQ){                                                                                            \
          if(ivars[i] != cmp_values[i]){                                                                                      \
            flag = 1;                                                                                                         \
            break;                                                                                                            \
          }                                                                                                                   \
        }else if(cmp == XBRTIME_CMP_NE){                                                                                      \
          if(ivars[i] == cmp_values[i]){                                                                                      \
            flag = 1;                                                                                                         \
            break;                                                                                                            \
          }                                                                                                                   \
        }else if(cmp == XBRTIME_CMP_GT){                                                                                      \
          if(ivars[i] <= cmp_values[i]){                                                                                      \
            flag = 1;                                                                                                         \
            break;                                                                                                            \
          }                                                                                                                   \
        }else if(cmp == XBRTIME_CMP_LE){                                                                                      \
          if(ivars[i] > cmp_values[i]){                                                                                       \
            flag = 1;                                                                                                         \
            break;                                                                                                            \
          }                                                                                                                   \
        }else if(cmp == XBRTIME_CMP_LT){                                                                                      \
          if(ivars[i] >= cmp_values[i]){                                                                                      \
            flag = 1;                                                                                                         \
            break;                                                                                                            \
          }                                                                                                                   \
        }else if(cmp == XBRTIME_CMP_GE){                                                                                      \
          if(ivars[i] < cmp_values[i]){                                                                                       \
            flag = 1;                                                                                                         \
            break;                                                                                                            \
          }                                                                                                                   \
        }                                                                                                                     \
      }                                                                                                                       \
    }                                                                                                                         \
    if(flag == 0){                                                                                                            \
      break;                                                                                                                  \
    }                                                                                                                         \
  }                                                                                                                           \
}

    /* Wait until all vector operations */
    XBGAS_WAIT_UNTIL_ALL_VECTOR(int, int)
    XBGAS_WAIT_UNTIL_ALL_VECTOR(long, long)
    XBGAS_WAIT_UNTIL_ALL_VECTOR(long long, longlong)
    XBGAS_WAIT_UNTIL_ALL_VECTOR(unsigned int, uint)
    XBGAS_WAIT_UNTIL_ALL_VECTOR(unsigned long, ulong)
    XBGAS_WAIT_UNTIL_ALL_VECTOR(unsigned long long, ulonglong)
    XBGAS_WAIT_UNTIL_ALL_VECTOR(int32_t, int32)
    XBGAS_WAIT_UNTIL_ALL_VECTOR(uint64_t, uint64)
    XBGAS_WAIT_UNTIL_ALL_VECTOR(uint32_t, uint32)
    XBGAS_WAIT_UNTIL_ALL_VECTOR(int64_t, int64)
    XBGAS_WAIT_UNTIL_ALL_VECTOR(size_t, size)
    XBGAS_WAIT_UNTIL_ALL_VECTOR(ptrdiff_t, ptrdiff)

#undef XBGAS_WAIT_UNTIL_ALL_VECTOR

#define XBGAS_WAIT_UNTIL_ANY_VECTOR(_type, _typename)                                                                           \ 
size_t xbrtime_##_typename##_wait_until_any_vector(_type *ivars, size_t nelems, const int *status, int cmp, _type *cmp_values)  \
{                                                                                                                               \
  size_t i;                                                                                                                     \
  int flag = 0;                                                                                                                 \
  for( i = 0; i < nelems; ++i ) {                                                                                               \
    if ( status[i] != 0 ) {                                                                                                     \
      flag = 1;                                                                                                                 \
      break;                                                                                                                    \
    }                                                                                                                           \
  }                                                                                                                             \
  if ( flag == 0 ) {                                                                                                            \
    return SIZE_MAX;                                                                                                            \
  }                                                                                                                             \
  while (1) {                                                                                                                   \
    for (i = 0; i < nelems; ++i) {                                                                                              \
      if (status[i] == 0) {                                                                                                     \
        if (cmp == XBRTIME_CMP_EQ) {                                                                                            \
          if (ivars[i] == cmp_values[i]) {                                                                                      \
            return i;                                                                                                           \
          }                                                                                                                     \
        } else if (cmp == XBRTIME_CMP_NE) {                                                                                     \
          if (ivars[i] != cmp_values[i]) {                                                                                      \ 
            return i;                                                                                                           \
          }                                                                                                                     \
        } else if (cmp == XBRTIME_CMP_GT) {                                                                                     \ 
          if (ivars[i] > cmp_values[i]) {                                                                                       \
            return i;                                                                                                           \
          }                                                                                                                     \
        } else if (cmp == XBRTIME_CMP_LE) {                                                                                     \
          if (ivars[i] <= cmp_values[i]) {                                                                                      \
            return i;                                                                                                           \
          }                                                                                                                     \
        } else if (cmp == XBRTIME_CMP_LT) {                                                                                     \
          if (ivars[i] < cmp_values[i]) {                                                                                       \  
            return i;                                                                                                           \
          }                                                                                                                     \
        } else if (cmp == XBRTIME_CMP_GE) {                                                                                     \
          if (ivars[i] >= cmp_values[i]) {                                                                                      \
            return i;                                                                                                           \
          }                                                                                                                     \
        }                                                                                                                       \
      }                                                                                                                         \
    }                                                                                                                           \
  }                                                                                                                             \
}

    /* Wait until any vector operations */
    XBGAS_WAIT_UNTIL_ANY_VECTOR(int, int)
    XBGAS_WAIT_UNTIL_ANY_VECTOR(long, long)
    XBGAS_WAIT_UNTIL_ANY_VECTOR(long long, longlong)
    XBGAS_WAIT_UNTIL_ANY_VECTOR(unsigned int, uint)
    XBGAS_WAIT_UNTIL_ANY_VECTOR(unsigned long, ulong)
    XBGAS_WAIT_UNTIL_ANY_VECTOR(unsigned long long, ulonglong)
    XBGAS_WAIT_UNTIL_ANY_VECTOR(int32_t, int32)
    XBGAS_WAIT_UNTIL_ANY_VECTOR(uint64_t, uint64)
    XBGAS_WAIT_UNTIL_ANY_VECTOR(uint32_t, uint32)
    XBGAS_WAIT_UNTIL_ANY_VECTOR(int64_t, int64)
    XBGAS_WAIT_UNTIL_ANY_VECTOR(size_t, size)
    XBGAS_WAIT_UNTIL_ANY_VECTOR(ptrdiff_t, ptrdiff)

#undef XBGAS_WAIT_UNTIL_ANY_VECTOR

#define XBGAS_WAIT_UNTIL_SOME_VECTOR(_type, _typename)                                                                                          \ 
size_t xbrtime_##_typename##_wait_until_some_vector(_type *ivars, size_t nelems, size_t *indices, const int *status, int cmp, _type *cmp_value) \
{                                                                                                                                               \
  size_t i;                                                                                                                                     \
  size_t j = 0;                                                                                                                                 \
  int flag = 0;                                                                                                                                 \
  while(1){                                                                                                                                     \
    flag = 0;                                                                                                                                   \
    for(i=0;i<nelems;++i){                                                                                                                      \
      if(status[i] == 0){                                                                                                                       \
        if(cmp == XBRTIME_CMP_EQ){                                                                                                              \
          if(ivars[i] == cmp_value[i]){                                                                                                         \
            indices[j] = i;                                                                                                                     \
            j++;                                                                                                                                \
            flag = 1;                                                                                                                           \
          }                                                                                                                                     \
        }else if(cmp == XBRTIME_CMP_NE){                                                                                                        \
          if(ivars[i] != cmp_value[i]){                                                                                                         \
            indices[j] = i;                                                                                                                     \
            j++;                                                                                                                                \
            flag = 1;                                                                                                                           \
          }                                                                                                                                     \
        }else if(cmp == XBRTIME_CMP_GT){                                                                                                        \
          if(ivars[i] > cmp_value[i]){                                                                                                          \
            indices[j] = i;                                                                                                                     \
            j++;                                                                                                                                \
            flag = 1;                                                                                                                           \
          }                                                                                                                                     \
        }else if(cmp == XBRTIME_CMP_LE){                                                                                                        \
          if(ivars[i] <= cmp_value[i]){                                                                                                         \
            indices[j] = i;                                                                                                                     \
            j++;                                                                                                                                \
            flag = 1;                                                                                                                           \
          }                                                                                                                                     \
        }else if(cmp == XBRTIME_CMP_LT){                                                                                                        \
          if(ivars[i] < cmp_value[i]){                                                                                                          \
            indices[j] = i;                                                                                                                     \
            j++;                                                                                                                                \
            flag = 1;                                                                                                                           \
          }                                                                                                                                     \
        }else if(cmp == XBRTIME_CMP_GE){                                                                                                        \
          if(ivars[i] >= cmp_value[i]){                                                                                                         \
            indices[j] = i;                                                                                                                     \
            j++;                                                                                                                                \ 
            flag = 1;                                                                                                                           \
          }                                                                                                                                     \
        }                                                                                                                                       \
      }                                                                                                                                         \
    }                                                                                                                                           \
    if(flag == 0){                                                                                                                              \
      break;                                                                                                                                    \
    }                                                                                                                                           \
  }                                                                                                                                             \
  return j;                                                                                                                                     \
}

    /* Wait until some vector operations */
    XBGAS_WAIT_UNTIL_SOME_VECTOR(int, int)
    XBGAS_WAIT_UNTIL_SOME_VECTOR(long, long)
    XBGAS_WAIT_UNTIL_SOME_VECTOR(long long, longlong)
    XBGAS_WAIT_UNTIL_SOME_VECTOR(unsigned int, uint)
    XBGAS_WAIT_UNTIL_SOME_VECTOR(unsigned long, ulong)
    XBGAS_WAIT_UNTIL_SOME_VECTOR(unsigned long long, ulonglong)
    XBGAS_WAIT_UNTIL_SOME_VECTOR(int32_t, int32)
    XBGAS_WAIT_UNTIL_SOME_VECTOR(uint64_t, uint64)
    XBGAS_WAIT_UNTIL_SOME_VECTOR(uint32_t, uint32)
    XBGAS_WAIT_UNTIL_SOME_VECTOR(int64_t, int64)
    XBGAS_WAIT_UNTIL_SOME_VECTOR(size_t, size)
    XBGAS_WAIT_UNTIL_SOME_VECTOR(ptrdiff_t, ptrdiff)

#undef XBGAS_WAIT_UNTIL_SOME_VECTOR
