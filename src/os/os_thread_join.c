#include "os_private.h"

#if SYS_OS == SYS_OS_LINUX

#include "atomics.h"

error_t __os_thread_join
(os_tid_t *set, void **ret_val)
{
    os_tid_t thread = *set;
    u8 *ptr = (u8 *)(thread + 1) - THREAD_STACK_SIZE;
    i32 tid = 0;

    *set = nullptr;

    while ((tid = atomic_load_i32(&thread->tid)) != 0)
    { __os_addr_wait_i32(&thread->tid, tid); }

    *ret_val = (void *)(uintptr_t)atomic_load_ssz((volatile ssz *)&thread->ret_val);

    __os_memory_free(&ptr, THREAD_STACK_SIZE);

    return success;
}

#else /* End - SYS_OS_LINUX */
#error "The current platform does not have a backend yet!"
#endif /* SYS_OS */
