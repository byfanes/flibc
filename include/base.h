#ifndef __FLIBC_BASE_H__
#define __FLIBC_BASE_H__

#define SYS_PAGE_SIZE_UNKNOWN 0
#define SYS_PAGE_SIZE_4K      4096
#define SYS_PAGE_SIZE_16K     16384

#define SYS_ABI_UNKNOWN 0
#define SYS_ABI_ILP32   1
#define SYS_ABI_LP64    2
#define SYS_ABI_LLP64   3

#define SYS_OS_UNKNOWN 0
#define SYS_OS_WINDOWS 1
#define SYS_OS_MACOS   2
#define SYS_OS_LINUX   3
#define SYS_OS_UNIX    4

#define SYS_ARCH_UNKNOWN 0
#define SYS_ARCH_X86     1
#define SYS_ARCH_X86_64  2
#define SYS_ARCH_ARM     3
#define SYS_ARCH_AARCH64 4
#define SYS_ARCH_RISCV64 5
#define SYS_ARCH_PPC64   6
#define SYS_ARCH_MIPS64  7
#define SYS_ARCH_WASM32  8
#define SYS_ARCH_WASM64  9

#define SYS_CC_UNKNOWN 0
#define SYS_CC_MSVC    1
#define SYS_CC_GCC     2
#define SYS_CC_CLANG   3
#define SYS_CC_INTEL   4

#define SYS_CVER_UNKNOWN 0
#define SYS_CVER_C89     1
#define SYS_CVER_C99     2
#define SYS_CVER_C11     3
#define SYS_CVER_C17     4
#define SYS_CVER_C23     5

#define SYS_CPPVER_UNKNOWN 0
#define SYS_CPPVER_CPP98   1
#define SYS_CPPVER_CPP11   2
#define SYS_CPPVER_CPP14   3
#define SYS_CPPVER_CPP17   4
#define SYS_CPPVER_CPP20   5
#define SYS_CPPVER_CPP23   6
#define SYS_CPPVER_CPP26   7

/* SYS_ISCPP */
#ifdef __cplusplus
    #define SYS_ISCPP 1
#else
    #define SYS_ISCPP 0
#endif

/* SYS_CPPVER */
#ifdef __cplusplus
    /* MSVC may report an old __cplusplus value unless /Zc:__cplusplus is enabled */
    #if defined(_MSVC_LANG)
        #define SYS_CPPVER_VALUE _MSVC_LANG
    #else
        #define SYS_CPPVER_VALUE __cplusplus
    #endif
    #if SYS_CPPVER_VALUE >= 202302L
        #define SYS_CPPVER SYS_CPPVER_CPP23
    #elif SYS_CPPVER_VALUE >= 202002L
        #define SYS_CPPVER SYS_CPPVER_CPP20
    #elif SYS_CPPVER_VALUE >= 201703L
        #define SYS_CPPVER SYS_CPPVER_CPP17
    #elif SYS_CPPVER_VALUE >= 201402L
        #define SYS_CPPVER SYS_CPPVER_CPP14
    #elif SYS_CPPVER_VALUE >= 201103L
        #define SYS_CPPVER SYS_CPPVER_CPP11
    #else
        #define SYS_CPPVER SYS_CPPVER_CPP98
    #endif
#else
    #define SYS_CPPVER SYS_CPPVER_UNKNOWN
#endif

/* SYS_CVER */
#ifdef __STDC_VERSION__
    #if __STDC_VERSION__ >= 202311L
        #define SYS_CVER SYS_CVER_C23
    #elif __STDC_VERSION__ >= 201710L
        #define SYS_CVER SYS_CVER_C17
    #elif __STDC_VERSION__ >= 201112L
        #define SYS_CVER SYS_CVER_C11
    #elif __STDC_VERSION__ >= 199901L
        #define SYS_CVER SYS_CVER_C99
    #else
        #define SYS_CVER SYS_CVER_C89
    #endif
#else
    #define SYS_CVER SYS_CVER_C89
#endif

/* SYS_CC */
#if defined(_MSC_VER)
    #define SYS_CC SYS_CC_MSVC
#elif defined(__clang__)
    #define SYS_CC SYS_CC_CLANG
#elif defined(__GNUC__)
    #define SYS_CC SYS_CC_GCC
#elif defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER)
    #define SYS_CC SYS_CC_INTEL
#else
    #define SYS_CC SYS_CC_UNKNOWN
#endif

/* SYS_ARCH */
#if defined(__x86_64__) || defined(_M_X64)
    #define SYS_ARCH SYS_ARCH_X86_64
#elif defined(__i386__) || defined(_M_IX86)
    #define SYS_ARCH SYS_ARCH_X86
#elif defined(__aarch64__) || defined(_M_ARM64)
    #define SYS_ARCH SYS_ARCH_AARCH64
#elif defined(__arm__) || defined(_M_ARM)
    #define SYS_ARCH SYS_ARCH_ARM
#elif defined(__riscv) && (__riscv_xlen == 64)
    #define SYS_ARCH SYS_ARCH_RISCV64
#else
    #define SYS_ARCH SYS_ARCH_UNKNOWN
#endif

/* SYS_OS */
#if defined(_WIN32) || defined(_WIN64)
    #define SYS_OS SYS_OS_WINDOWS
#elif defined(__APPLE__) && defined(__MACH__)
    #define SYS_OS SYS_OS_MACOS
#elif defined(__linux__)
    #define SYS_OS SYS_OS_LINUX
#elif defined(__unix__) || defined(__unix)
    #define SYS_OS SYS_OS_UNIX
#else
    #define SYS_OS SYS_OS_UNKNOWN
#endif

/* SYS_ABI */
#if SYS_OS == SYS_OS_WINDOWS && \
    (SYS_ARCH == SYS_ARCH_X86_64 || SYS_ARCH == SYS_ARCH_AARCH64)
    #define SYS_ABI SYS_ABI_LLP64
#elif SYS_ARCH == SYS_ARCH_X86_64 || \
      SYS_ARCH == SYS_ARCH_AARCH64 || \
      SYS_ARCH == SYS_ARCH_RISCV64
    #define SYS_ABI SYS_ABI_LP64
#else
    #define SYS_ABI SYS_ABI_ILP32
#endif

/* SYS_PAGE_SIZE */
#if SYS_OS == SYS_OS_MACOS && SYS_ARCH == SYS_ARCH_AARCH64
    #define SYS_PAGE_SIZE SYS_PAGE_SIZE_16K
#elif SYS_ARCH == SYS_ARCH_AARCH64 && SYS_OS != SYS_OS_WINDOWS
    /* Most ARM64 systems are 4K unless configured otherwise */
    #define SYS_PAGE_SIZE SYS_PAGE_SIZE_4K
#else
    #define SYS_PAGE_SIZE SYS_PAGE_SIZE_4K
#endif

/* __no_return */
#if SYS_CC == SYS_CC_MSVC
    #define __no_return __declspec(noreturn)
#elif SYS_CC == SYS_CC_GCC || SYS_CC == SYS_CC_CLANG
    #define __no_return __attribute__((__noreturn__))
#elif SYS_CVER >= SYS_CVER_C23
    #define __no_return [[noreturn]]
#elif SYS_CVER >= SYS_CVER_C11
    #define __no_return _Noreturn
#else
    #define __no_return
#endif

/* Extension: We are using _Noreturn for compilers to not yap about after
 * calling function like abort/exit and for other static analyzers
 */
#if SYS_CC == SYS_CC_MSVC
    #define __unreachable() __assume(0)
#elif SYS_CC == SYS_CC_GCC || SYS_CC == SYS_CC_CLANG
    #define __unreachable() __builtin_unreachable()
#else
    #define __unreachable()
#endif

/* Extension: We use compiler's offset because this is usable in compiler
 * time which allows use to check offsets of the element which is usefull
 * for checking slice and dynamic arrays
 */
#define offsetof(type, member) __builtin_offsetof(type, member)

#define noreturn __no_return void

/* Instead of NULL being ((void *)0)
 * we use integer zero which is 'null' 0 and for
 * pointer null which is 'nullptr' ((void *)0)
 */
#define null 0
#if !SYS_ISCPP
    #define nullptr ((void *)0)
#endif

#define FLIBC_STACK_THRESHOLD 4096
#define FLIBC_FILE_BUFFER_SIZE 4096
#define FLIBC_FMT_TMP_BUF_SIZE 64

/* Extension:
 * C89 does not provide standardized fixed-width integer types so we use
 * a few compiler and platform-specific extensions to define 64-bit types
 * This improves portability and helps ensure consistent behavior across
 * modern systems
 */
/* 64-bit */
#if SYS_ABI == SYS_ABI_LLP64
    /* Windows 64-bit long is 32-bit use compiler extensions */
    #if SYS_CC == SYS_CC_GCC || SYS_CC == SYS_CC_CLANG
        __extension__ typedef   signed long long s64;
        __extension__ typedef unsigned long long u64;
    #else
        typedef   signed __int64 s64;
        typedef unsigned __int64 u64;
    #endif
#elif SYS_ABI == SYS_ABI_LP64
    /* Unix-like 64-bit long is 64-bit */
    typedef   signed long s64;
    typedef unsigned long u64;
#else
    /* ILP32: long is 32-bit use long long */
    #if SYS_CC == SYS_CC_GCC || SYS_CC == SYS_CC_CLANG
        __extension__ typedef   signed long long s64;
        __extension__ typedef unsigned long long u64;
    #else
        typedef   signed long long s64;
        typedef unsigned long long u64;
    #endif
#endif

typedef   signed char      s8;
typedef unsigned char      u8;
typedef   signed short     s16;
typedef unsigned short     u16;
typedef   signed int       s32;
typedef unsigned int       u32;

/* pointer-sized */
#if SYS_ABI == SYS_ABI_LP64 || SYS_ABI == SYS_ABI_LLP64
    /* 64-bit ABI */
    typedef s64 intptr_t;
    typedef u64 uintptr_t;
    typedef u64 usz;
    typedef s64 ssz;
#else
    /* 32-bit ABI */
    typedef s32 intptr_t;
    typedef u32 uintptr_t;
    typedef u32 usz;
    typedef s32 ssz;
#endif

/* This types helps developers to know what is expected from the pointer */
typedef u8*        cstr_t;
typedef const u8* ccstr_t;

/* Booleans */
#if !SYS_ISCPP && (SYS_CVER < SYS_CVER_C23 && !defined(__bool_true_false_are_defined))
    typedef u8 bool;
    #define true 1
    #define false 0
    #define __bool_true_false_are_defined 1
#endif

/* _Nullable is just an annotation to know which function parameters can safely be null */
#ifndef _Nullable
    #define _Nullable
#endif

#endif /* __FLIBC_BASE_H__ */
