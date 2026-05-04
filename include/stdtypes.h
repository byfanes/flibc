#ifndef __FLIBC_STDTYPES_H__
#define __FLIBC_STDTYPES_H__

/* 8-bit */
typedef signed char        int8_t;
typedef unsigned char      uint8_t;

/* 16-bit */
#if __SIZEOF_SHORT__ == 2
typedef short              int16_t;
typedef unsigned short     uint16_t;
#else
#error "No 16-bit type found"
#endif

/* 32-bit */
#if __SIZEOF_INT__ == 4
typedef int                int32_t;
typedef unsigned int       uint32_t;
#elif __SIZEOF_LONG__ == 4
typedef long               int32_t;
typedef unsigned long      uint32_t;
#else
#error "No 32-bit type found"
#endif

/* 64-bit */
#if __SIZEOF_LONG__ == 8
typedef long               int64_t;
typedef unsigned long      uint64_t;
#elif __SIZEOF_LONG_LONG__ == 8
typedef long long          int64_t;
typedef unsigned long long uint64_t;
#else
#error "No 64-bit type found"
#endif

/* pointer-sized */
#if __SIZEOF_POINTER__ == 8
typedef int64_t  intptr_t;
typedef uint64_t uintptr_t;
typedef int64_t  arch_t;
#elif __SIZEOF_POINTER__ == 4
typedef int32_t  intptr_t;
typedef uint32_t uintptr_t;
typedef int32_t  arch_t;
#else
#error "Unsupported pointer size"
#endif

typedef  uint8_t  u8;
typedef   int8_t  i8;
typedef uint16_t u16;
typedef  int16_t i16;
typedef uint32_t u32;
typedef  int32_t i32;
typedef uint64_t u64;
typedef  int64_t i64;

#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 202311L
    typedef u8 bool;
    #define true 1
    #define false 0
    #define __bool_true_false_are_defined 1
#endif

#define  uint8_t ()
#define   int8_t ()
#define uint16_t ()
#define  int16_t ()
#define uint32_t ()
#define  int32_t ()
#define uint64_t ()
#define  int64_t ()


#define NULL 0
#define nullptr ((void*)0)

#define arch_size (sizeof(void*))

#define CONCAT_IMPL(a, b) a ## b
#define CONCAT(a, b) CONCAT_IMPL(a, b)

#define FLIBC_STACK_THRESHOLD 4096

#endif /* __FLIBC_STDTYPES_H__ */
