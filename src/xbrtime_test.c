/*
 * _XBRTIME_TEST_C_
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

#define XBGAS_TEST(_type, _typename)                                           \
int xbrtime_##_typename##_test(_type *ivar, int cmp, _type cmp_value)          \
{                                                                              \ 
  if(cmp == XBRTIME_CMP_EQ){                                                   \
    if(*ivar == cmp_value){                                                    \
      return 1;                                                                \
    }                                                                          \
  }else if(cmp == XBRTIME_CMP_NE){                                             \
    if(*ivar != cmp_value){                                                    \
      return 1;                                                                \
    }                                                                          \
  }else if(cmp == XBRTIME_CMP_GT){                                             \
    if(*ivar > cmp_value){                                                     \
      return 1;                                                                \
    }                                                                          \
  }else if(cmp == XBRTIME_CMP_LE){                                             \
    if(*ivar <= cmp_value){                                                    \
      return 1;                                                                \
    }                                                                          \
  }else if(cmp == XBRTIME_CMP_LT){                                             \
    if(*ivar < cmp_value){                                                     \
      return 1;                                                                \
    }                                                                          \
  }else if(cmp == XBRTIME_CMP_GE){                                             \
    if(*ivar >= cmp_value){                                                    \
      return 1;                                                                \  
    }                                                                          \
  }                                                                            \
  return 0;                                                                    \
}

    /* Test operations */
    XBGAS_TEST(int, int)
    XBGAS_TEST(long, long)
    XBGAS_TEST(long long, longlong)
    XBGAS_TEST(unsigned int, uint)
    XBGAS_TEST(unsigned long, ulong)
    XBGAS_TEST(unsigned long long, ulonglong)
    XBGAS_TEST(int32_t, int32)
    XBGAS_TEST(uint64_t, uint64)
    XBGAS_TEST(uint32_t, uint32)
    XBGAS_TEST(int64_t, int64)
    XBGAS_TEST(size_t, size)
    XBGAS_TEST(ptrdiff_t, ptrdiff)

#undef XBGAS_TEST

#define XBGAS_TEST_ALL(_type, _typename)                                                                          \ 
int xbrtime_##_typename##_test_all(_type *ivars, size_t nelems, const int *status, int cmp, _type cmp_value)      \
{                                                                                                                 \
  size_t i;                                                                                                       \
  for(i=0;i<nelems;++i){                                                                                          \
    if(status[i] == 0){                                                                                           \
      if(cmp == XBRTIME_CMP_EQ){                                                                                  \
        if(ivars[i] != cmp_value){                                                                                \
          return 0;                                                                                               \
        }                                                                                                         \
      }else if(cmp == XBRTIME_CMP_NE){                                                                            \  
        if(ivars[i] == cmp_value){                                                                                \
          return 0;                                                                                               \
        }                                                                                                         \
      }else if(cmp == XBRTIME_CMP_GT){                                                                            \
        if(ivars[i] <= cmp_value){                                                                                \
          return 0;                                                                                               \
        }                                                                                                         \
      }else if(cmp == XBRTIME_CMP_LE){                                                                            \
        if(ivars[i] > cmp_value){                                                                                 \
          return 0;                                                                                               \
        }                                                                                                         \
      }else if(cmp == XBRTIME_CMP_LT){                                                                            \
        if(ivars[i] >= cmp_value){                                                                                \
          return 0;                                                                                               \
        }                                                                                                         \
      }else if(cmp == XBRTIME_CMP_GE){                                                                            \
        if(ivars[i] < cmp_value){                                                                                 \
          return 0;                                                                                               \
        }                                                                                                         \
      }                                                                                                           \
    }                                                                                                             \
  }                                                                                                               \                                                                 
  return 1;                                                                                                       \
}

    /* Test all operations */
    XBGAS_TEST_ALL(int, int)
    XBGAS_TEST_ALL(long, long)
    XBGAS_TEST_ALL(long long, longlong)
    XBGAS_TEST_ALL(unsigned int, uint)
    XBGAS_TEST_ALL(unsigned long, ulong)
    XBGAS_TEST_ALL(unsigned long long, ulonglong)
    XBGAS_TEST_ALL(int32_t, int32)
    XBGAS_TEST_ALL(uint64_t, uint64)
    XBGAS_TEST_ALL(uint32_t, uint32)
    XBGAS_TEST_ALL(int64_t, int64)
    XBGAS_TEST_ALL(size_t, size)
    XBGAS_TEST_ALL(ptrdiff_t, ptrdiff)

#undef XBGAS_TEST_ALL

#define XBGAS_TEST_ANY(_type, _typename)                                                                        \ 
size_t xbrtime_##_typename##_test_any(_type *ivars, size_t nelems, const int *status, int cmp, _type cmp_value) \
{                                                                                                               \
  size_t i;                                                                                                     \
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
  return SIZE_MAX;                                                                                              \
}                                                                                                                

    /* Test any operations */
    XBGAS_TEST_ANY(int, int)
    XBGAS_TEST_ANY(long, long)
    XBGAS_TEST_ANY(long long, longlong)
    XBGAS_TEST_ANY(unsigned int, uint)
    XBGAS_TEST_ANY(unsigned long, ulong)
    XBGAS_TEST_ANY(unsigned long long, ulonglong)
    XBGAS_TEST_ANY(int32_t, int32)
    XBGAS_TEST_ANY(uint64_t, uint64)
    XBGAS_TEST_ANY(uint32_t, uint32)
    XBGAS_TEST_ANY(int64_t, int64)
    XBGAS_TEST_ANY(size_t, size)
    XBGAS_TEST_ANY(ptrdiff_t, ptrdiff)

#undef XBGAS_TEST_ANY

#define XBGAS_TEST_SOME(_type, _typename)                                                                                         \ 
size_t xbrtime_##_typename##_test_some(_type *ivars, size_t nelems, size_t *indices, const int *status, int cmp, _type cmp_value) \ 
{                                                                                                                                 \
  size_t i;                                                                                                                       \
  size_t j = 0;                                                                                                                   \
  for(i=0;i<nelems;++i){                                                                                                          \
    if(status[i] == 0){                                                                                                           \
      if(cmp == XBRTIME_CMP_EQ){                                                                                                  \
        if(ivars[i] == cmp_value){                                                                                                \
          indices[j] = i;                                                                                                         \
          j++;                                                                                                                    \
        }                                                                                                                         \
      }else if(cmp == XBRTIME_CMP_NE){                                                                                            \
        if(ivars[i] != cmp_value){                                                                                                \
          indices[j] = i;                                                                                                         \ 
          j++;                                                                                                                    \
        }                                                                                                                         \
      }else if(cmp == XBRTIME_CMP_GT){                                                                                            \
        if(ivars[i] > cmp_value){                                                                                                 \
          indices[j] = i;                                                                                                         \
          j++;                                                                                                                    \
        }                                                                                                                         \
      }else if(cmp == XBRTIME_CMP_LE){                                                                                            \
        if(ivars[i] <= cmp_value){                                                                                                \
          indices[j] = i;                                                                                                         \
          j++;                                                                                                                    \
        }                                                                                                                         \
      }else if(cmp == XBRTIME_CMP_LT){                                                                                            \
        if(ivars[i] < cmp_value){                                                                                                 \
          indices[j] = i;                                                                                                         \
          j++;                                                                                                                    \
        }                                                                                                                         \
      }else if(cmp == XBRTIME_CMP_GE){                                                                                            \
        if(ivars[i] >= cmp_value){                                                                                                \
          indices[j] = i;                                                                                                         \
          j++;                                                                                                                    \
        }                                                                                                                         \
      }                                                                                                                           \
    }                                                                                                                             \
  }                                                                                                                               \
  return j;                                                                                                                       \
}

    /* Test some operations */
    XBGAS_TEST_SOME(int, int)
    XBGAS_TEST_SOME(long, long)
    XBGAS_TEST_SOME(long long, longlong)
    XBGAS_TEST_SOME(unsigned int, uint)
    XBGAS_TEST_SOME(unsigned long, ulong)
    XBGAS_TEST_SOME(unsigned long long, ulonglong)
    XBGAS_TEST_SOME(int32_t, int32)
    XBGAS_TEST_SOME(uint64_t, uint64)
    XBGAS_TEST_SOME(uint32_t, uint32)
    XBGAS_TEST_SOME(int64_t, int64)
    XBGAS_TEST_SOME(size_t, size)
    XBGAS_TEST_SOME(ptrdiff_t, ptrdiff)

#undef XBGAS_TEST_SOME

#define XBGAS_TEST_ALL_VECTOR(_type, _typename)                                                                             \ 
int xbrtime_##_typename##_test_all_vector(_type *ivars, size_t nelems, const int *status, int cmp, _type *cmp_values)      \
{                                                                                                                           \
  size_t i;                                                                                                                 \
  for(i=0;i<nelems;++i){                                                                                                    \
    if(status[i] == 0){                                                                                                     \ 
      if(cmp == XBRTIME_CMP_EQ){                                                                                            \
        if(ivars[i] != cmp_values[i]){                                                                                      \
          return 0;                                                                                                         \
        }                                                                                                                   \
      }else if(cmp == XBRTIME_CMP_NE){                                                                                      \
        if(ivars[i] == cmp_values[i]){                                                                                      \
          return 0;                                                                                                         \
        }                                                                                                                   \
      }else if(cmp == XBRTIME_CMP_GT){                                                                                      \
        if(ivars[i] <= cmp_values[i]){                                                                                      \
          return 0;                                                                                                         \
        }                                                                                                                   \
      }else if(cmp == XBRTIME_CMP_LE){                                                                                      \
        if(ivars[i] > cmp_values[i]){                                                                                       \
          return 0;                                                                                                         \
        }                                                                                                                   \
      }else if(cmp == XBRTIME_CMP_LT){                                                                                      \
        if(ivars[i] >= cmp_values[i]){                                                                                      \
          return 0;                                                                                                         \
        }                                                                                                                   \
      }else if(cmp == XBRTIME_CMP_GE){                                                                                      \
        if(ivars[i] < cmp_values[i]){                                                                                       \
          return 0;                                                                                                         \
        }                                                                                                                   \
      }                                                                                                                     \
    }                                                                                                                       \
  }                                                                                                                         \
  return 1;                                                                                                                 \
}

    /* Test all vector operations */
    XBGAS_TEST_ALL_VECTOR(int, int)
    XBGAS_TEST_ALL_VECTOR(long, long)
    XBGAS_TEST_ALL_VECTOR(long long, longlong)
    XBGAS_TEST_ALL_VECTOR(unsigned int, uint)
    XBGAS_TEST_ALL_VECTOR(unsigned long, ulong)
    XBGAS_TEST_ALL_VECTOR(unsigned long long, ulonglong)
    XBGAS_TEST_ALL_VECTOR(int32_t, int32)
    XBGAS_TEST_ALL_VECTOR(uint64_t, uint64)
    XBGAS_TEST_ALL_VECTOR(uint32_t, uint32)
    XBGAS_TEST_ALL_VECTOR(int64_t, int64)
    XBGAS_TEST_ALL_VECTOR(size_t, size)
    XBGAS_TEST_ALL_VECTOR(ptrdiff_t, ptrdiff)

#undef XBGAS_TEST_ALL_VECTOR

#define XBGAS_TEST_ANY_VECTOR(_type, _typename)                                                                               \ 
size_t xbrtime_##_typename##_test_any_vector(_type *ivars, size_t nelems, const int *status, int cmp, _type *cmp_values)      \
{                                                                                                                             \
  size_t i;                                                                                                                   \
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
  return SIZE_MAX;                                                                                                            \
}

    /* Test any vector operations */
    XBGAS_TEST_ANY_VECTOR(int, int)
    XBGAS_TEST_ANY_VECTOR(long, long)
    XBGAS_TEST_ANY_VECTOR(long long, longlong)
    XBGAS_TEST_ANY_VECTOR(unsigned int, uint)
    XBGAS_TEST_ANY_VECTOR(unsigned long, ulong)
    XBGAS_TEST_ANY_VECTOR(unsigned long long, ulonglong)
    XBGAS_TEST_ANY_VECTOR(int32_t, int32)
    XBGAS_TEST_ANY_VECTOR(uint64_t, uint64)
    XBGAS_TEST_ANY_VECTOR(uint32_t, uint32)
    XBGAS_TEST_ANY_VECTOR(int64_t, int64)
    XBGAS_TEST_ANY_VECTOR(size_t, size)
    XBGAS_TEST_ANY_VECTOR(ptrdiff_t, ptrdiff)

#undef XBGAS_TEST_ANY_VECTOR

#define XBGAS_TEST_SOME_VECTOR(_type, _typename)                                                                                              \ 
size_t xbrtime_##_typename##_test_some_vector(_type *ivars, size_t nelems, size_t *indices, const int *status, int cmp, _type *cmp_value)     \
{                                                                                                                                             \
  size_t i;                                                                                                                                   \
  size_t j = 0;                                                                                                                               \
  for(i=0;i<nelems;++i){                                                                                                                      \
    if(status[i] == 0){                                                                                                                       \
      if(cmp == XBRTIME_CMP_EQ){                                                                                                              \
        if(ivars[i] == cmp_value[i]){                                                                                                         \
          indices[j] = i;                                                                                                                     \
          j++;                                                                                                                                \
        }                                                                                                                                     \
      }else if(cmp == XBRTIME_CMP_NE){                                                                                                        \
        if(ivars[i] != cmp_value[i]){                                                                                                         \
          indices[j] = i;                                                                                                                     \
          j++;                                                                                                                                \
        }                                                                                                                                     \
      }else if(cmp == XBRTIME_CMP_GT){                                                                                                        \
        if(ivars[i] > cmp_value[i]){                                                                                                          \
          indices[j] = i;                                                                                                                     \
          j++;                                                                                                                                \
        }                                                                                                                                     \
      }else if(cmp == XBRTIME_CMP_LE){                                                                                                        \
        if(ivars[i] <= cmp_value[i]){                                                                                                         \
          indices[j] = i;                                                                                                                     \
          j++;                                                                                                                                \
        }                                                                                                                                     \
      }else if(cmp == XBRTIME_CMP_LT){                                                                                                        \
        if(ivars[i] < cmp_value[i]){                                                                                                          \
          indices[j] = i;                                                                                                                     \
          j++;                                                                                                                                \
        }                                                                                                                                     \
      }else if(cmp == XBRTIME_CMP_GE){                                                                                                        \
        if(ivars[i] >= cmp_value[i]){                                                                                                         \
          indices[j] = i;                                                                                                                     \
          j++;                                                                                                                                \ 
        }                                                                                                                                     \
      }                                                                                                                                       \
    }                                                                                                                                         \
  }                                                                                                                                           \
  return j;                                                                                                                                   \
}

    /* Test some vector operations */
    XBGAS_TEST_SOME_VECTOR(int, int)
    XBGAS_TEST_SOME_VECTOR(long, long)
    XBGAS_TEST_SOME_VECTOR(long long, longlong)
    XBGAS_TEST_SOME_VECTOR(unsigned int, uint)
    XBGAS_TEST_SOME_VECTOR(unsigned long, ulong)
    XBGAS_TEST_SOME_VECTOR(unsigned long long, ulonglong)
    XBGAS_TEST_SOME_VECTOR(int32_t, int32)
    XBGAS_TEST_SOME_VECTOR(uint64_t, uint64)
    XBGAS_TEST_SOME_VECTOR(uint32_t, uint32)
    XBGAS_TEST_SOME_VECTOR(int64_t, int64)
    XBGAS_TEST_SOME_VECTOR(size_t, size)
    XBGAS_TEST_SOME_VECTOR(ptrdiff_t, ptrdiff)

#undef XBGAS_TEST_SOME_VECTOR

/* EOF */
