#include "os_private.h"

#if SYS_OS == SYS_OS_LINUX

#include "atomics.h"

error_t __os_thread_join
(void **thread_handle, void **ret_val)
{
    thread_ctrl_t *ctrl = *thread_handle;
    u8 *ptr = (u8 *)(ctrl + 1) - THREAD_STACK_SIZE;

    while(!atomic_load_ssz(&ctrl->done))
    { __os_thread_yield(); }

    *ret_val = (void *)(uintptr_t)atomic_load_ssz(&ctrl->ret_val);

    __os_memory_free(&ptr, THREAD_STACK_SIZE);

    *thread_handle = nullptr;
    return success;
}

#else /* End - SYS_OS_LINUX */
#error "The current platform does not have a backend yet!"
#endif /* SYS_OS */
