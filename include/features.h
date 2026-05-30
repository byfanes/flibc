#ifndef __FLIBC_FEATURES_H__
#define __FLIBC_FEATURES_H__

#if defined(__GNUC__)
#define _Noreturn __attribute__((__noreturn__))
#else /* defined(__GNUC__) */
#define _Noreturn [[noreturn]]
#endif

#ifndef __STDC_VERSION__
#define __STDC_VERSION__ 0L
#endif /* __STDC_VERSION__ - c89 does not have this macro */

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

#ifndef _Nullable
#define _Nullable
#endif /* _Nullable */

#define __unreachable() \
    for(;;) __builtin_unreachable();

#endif /* __FLIBC_FEATURES_H__ */
