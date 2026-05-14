#ifndef __FLIBC_SYSCALL_H__
#define __FLIBC_SYSCALL_H__

#include "features.h"
#include "stdtypes.h"

#if defined(__x86_64__)
    #include "../src/arch/x86_64/syscall_arch.h"
#else
    #error "Architecture not supported by flibc yet!"
#endif

#endif /* __FLIBC_SYSCALL_H__ */
