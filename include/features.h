#ifndef __FLIBC_FEATURES_H__
#define __FLIBC_FEATURES_H__

#define INTERNAL static inline

#if defined(__GNUC__)
#define _Noreturn __attribute__((__noreturn__))
#else /* defined(__GNUC__) */
#define _Noreturn [[noreturn]]
#endif

#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 202311L
#define typeof __typeof__
#endif

#define __unreachable() \
    for(;;) __builtin_unreachable();

#endif /* __FLIBC_FEATURES_H__ */
