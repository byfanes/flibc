#ifndef __FLIBC_SYSCALL_H__
#define __FLIBC_SYSCALL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "base.h"

#if defined(__x86_64__)
    #include "../src/arch/syscall_arch.h"
#else
    #error "Architecture not supported by flibc yet!"
#endif

#ifdef __cplusplus
}
#endif

#endif /* __FLIBC_SYSCALL_H__ */
