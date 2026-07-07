#ifndef __FLIBC_BASE_H__
#define __FLIBC_BASE_H__

#ifndef __STDC_VERSION__
#define __STDC_VERSION__ 0L
#endif /* __STDC_VERSION__ - c89 does not have this macro */

#ifndef _Nullable
#define _Nullable
#endif /* _Nullable */

#define __unreachable() __builtin_unreachable()

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

/* Extensin:
 * C89 does not provide standardized fixed-width integer types so we use
 * a few compiler and platform-specific extensions to define 64-bit types
 * This improves portability and helps ensure consistent behavior across
 * modern systems
 */
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
#elif defined(__x86_64__) || defined(__aarch64__) || defined(__LP64__)
    /* 64-bit Linux / macOS / Unix (LP64): long is natively 64-bit */
    typedef long               int64_t;
    typedef unsigned long      uint64_t;
#else
    /* 32-bit Linux / Unix: long is 32-bit, so we MUST use long long for 64-bit types */
    __extension__ typedef long long          int64_t;
    __extension__ typedef unsigned long long uint64_t;
#endif

/* pointer-sized */
#if defined(__x86_64__) || defined(__aarch64__) || defined(_WIN64) || defined(__LP64__)
    /* 64-bit architectures */
    typedef  int64_t intptr_t;
    typedef uint64_t uintptr_t;
    typedef uint64_t usize_t;
    typedef  int64_t ssize_t;
#else
    /* 32-bit architectures */
    typedef  int32_t intptr_t;
    typedef uint32_t uintptr_t;
    typedef uint32_t usize_t;
    typedef  int32_t ssize_t;
#endif

/* short aliases */
typedef  uint8_t  u8;
typedef   int8_t  i8;
typedef uint16_t u16;
typedef  int16_t i16;
typedef uint32_t u32;
typedef  int32_t i32;
typedef uint64_t u64;
typedef  int64_t i64;
typedef  usize_t usz;
typedef  ssize_t ssz;

#ifdef __x86_64__
#define SIZE_IS_64BITS
#endif

/* Booleans */
#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 202311L
    typedef u8 bool;
    #define true 1
    #define false 0
    #define __bool_true_false_are_defined 1
#endif

/* Extension: We are using _Noreturn for compilers to not yap about after
 * calling function like abort/exit and for other static analyzers
 */
#if defined(__GNUC__) || defined(__clang__)
#define _Noreturn __attribute__((__noreturn__))
#elif __STDC_VERSION__ >= 201112L
#define _Noreturn _Noreturn
#else
#define _Noreturn
#endif

#define NULL 0
#define nullptr ((void*)0)

/* Extension: We use compiler's offset because this is usable in compiler
 * time which allows use to check offsets of the element which is usefull
 * for checking slice and dynamic arrays
 */
#define offsetof(type, member) __builtin_offsetof(type, member)

#define ARRAY_LEN(x) (sizeof((x)) / sizeof((x)[0]))

#define CONCAT_IMPL(a, b) a ## b
#define CONCAT(a, b) CONCAT_IMPL(a, b)

#define FLIBC_STACK_THRESHOLD 4096
#define FLIBC_FILE_BUFFER_SIZE 4096

/* Note: We might add a config stage while compiling to get excat values */
/* Most systems uses 4KiB in some systems it might different
 * such as 16KiB in macos(apple-chips) and ios systems.
 */
#ifndef PAGE_SIZE
#define PAGE_SIZE (1024*4)
#endif /* PAGE_SIZE */

/* Extension: We are using builtin args from the compiler because its the safe
 * way to do we can add them manually with some pointer arithmetic but it
 * wont be safe and wont be that compatiable with other architectures
 */
typedef __builtin_va_list va_list;
#define va_start(v,l)   __builtin_va_start(v,l)
#define va_end(v)       __builtin_va_end(v)
#define va_arg(v,l)     __builtin_va_arg(v,l)
#define va_copy(d,s)    __builtin_va_copy(d,s)

#ifdef __cplusplus
}
#endif

#endif /* __FLIBC_BASE_H__ */
