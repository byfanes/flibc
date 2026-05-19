#ifndef __FLIBC_STDTYPES_H__
#define __FLIBC_STDTYPES_H__

#ifdef __cplusplus
extern "C" {
#endif

/* 8-bit */
typedef signed char        int8_t;
typedef unsigned char      uint8_t;

/* 16-bit
 * (short is guaranteed 16-bit on all 64-bit OS architectures)
 */
typedef short              int16_t;
typedef unsigned short     uint16_t;

/* 32-bit
 * (int is guaranteed 32-bit on all 64-bit OS architectures)
 */
typedef int                int32_t;
typedef unsigned int       uint32_t;

/* 64-bit */
#if defined(_WIN32) || defined(_WIN64)
    /* Windows (LLP64): long is only 32-bit. We must use extensions. */
    #if defined(__GNUC__) || defined(__clang__)
        __extension__ typedef long long          int64_t;
        __extension__ typedef unsigned long long uint64_t;
    #else
        /* MSVC / cl.exe */
        typedef __int64          int64_t;
        typedef unsigned __int64 uint64_t;
    #endif
#else
    /* Linux / macOS / Unix (LP64): long is natively 64-bit */
    typedef long               int64_t;
    typedef unsigned long      uint64_t;
#endif

/* pointer-sized */
typedef  int64_t intptr_t;
typedef uint64_t uintptr_t;
typedef uint64_t usize_t;
typedef  int64_t ssize_t;

/* short aliases */
typedef  uint8_t  u8;
typedef   int8_t  i8;
typedef uint16_t u16;
typedef  int16_t i16;
typedef uint32_t u32;
typedef  int32_t i32;
typedef uint64_t u64;
typedef  int64_t i64;

/* Booleans */
#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 202311L
    typedef u8 bool;
    #define true 1
    #define false 0
    #define __bool_true_false_are_defined 1
#endif

#define NULL 0
#define nullptr ((void*)0)

#define arch_size (sizeof(void*))

#define CONCAT_IMPL(a, b) a ## b
#define CONCAT(a, b) CONCAT_IMPL(a, b)

#define FLIBC_STACK_THRESHOLD 4096

#ifdef __cplusplus
}
#endif

#endif /* __FLIBC_STDTYPES_H__ */
