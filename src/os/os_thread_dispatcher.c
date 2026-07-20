#include "os_private.h"

#if SYS_OS == SYS_OS_LINUX

extern ssz atomic_xchg_ssz(volatile ssz* ptr, ssz new_val);

/* This function is used in assembly for setting the thread_t safetly because
 * if the struct thread_s changes we need to change assembly to so we can just
 * do it in C and let the compiler handle the offsets
 */
noreturn __os_thread_dispatcher
(os_tid_t thread)
{
    /* Init variables */
    void *ret = 0;

    /* Changing the function so the arg and std pointers will be in correct place */
    if(thread->std) {
        ret = thread->std_funcs.with(thread->std, thread->arg);
    } else {
        ret = thread->std_funcs.without(thread->arg);
    }

    atomic_xchg_ssz((volatile ssz *)&thread->ret_val, (ssz)(uintptr_t)ret);

    __os_exit(0);
}

#else /* End - SYS_OS_LINUX */
#error "The current platform does not have a backend yet!"
#endif /* SYS_OS */
