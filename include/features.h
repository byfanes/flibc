#ifndef __FLIBC_FEATURES_H__
#define __FLIBC_FEATURES_H__


#if defined(__GNUC__)
#define _Noreturn __attribute__((__noreturn__))
#define __dont_optimize__ volatile
#else /* defined(__GNUC__) */
#define _Noreturn [[noreturn]]
#define __dont_optimize__
#endif

#if __STDC_VERSION__ >= 199901L
#define INLINE inline
#elif defined(__GNUC__) || defined(__clang__)
#define INLINE __inline__
#elif defined(_MSC_VER)
#define INLINE __inline
#else
#define INLINE
#endif

#define INTERNAL static INLINE

#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 202311L
#define typeof __typeof__
#endif

#define __unreachable() \
    for(;;) __builtin_unreachable();

#endif /* __FLIBC_FEATURES_H__ */
