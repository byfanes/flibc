#include "os_private.h"

#if SYS_OS == SYS_OS_LINUX

error_t __os_thread_new
(void **thread_ctrl, void *(*func)(struct std_s *, void *), struct std_s *std, void *arg)
{
    /* Init variables */
    ssz ret = 0;
    u8 *stack = nullptr;
    error_t res = 0;
    thread_ctrl_t *ctrl = nullptr;

    res = __os_memory_alloc(&stack, THREAD_STACK_SIZE);
    if(res) { goto cleanup; }

    ctrl = (thread_ctrl_t *)(uintptr_t)(stack + THREAD_STACK_SIZE - sizeof(thread_ctrl_t));

    /* Set thread control to defaults */
    ctrl->done = false;
    ctrl->ret_val = 0;

    /* Create the new thread */
    ret = __thread_clone_linux(THREAD_FLAGS, ctrl, func, std, arg);

    if(0 > ret && ret > -MAX_ERRNO) {
        res = __os_error_map(ret);
        goto cleanup;
    }

    *thread_ctrl = ctrl;
    return res;
cleanup:
    if(stack) { __os_memory_free(&stack, THREAD_STACK_SIZE);}
    return res;
}

#else /* End - SYS_OS_LINUX */
#error "The current platform does not have a backend yet!"
#endif /* SYS_OS */
