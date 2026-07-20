#include "os_private.h"

#if SYS_OS == SYS_OS_LINUX

error_t __os_thread_new
(os_tid_t *set, f_std_thread_func func, struct std_s *std, void *arg)
{
    /* Init variables */
    ssz ret = 0;
    char *stack = nullptr;
    error_t res = 0;
    os_tid_t disp = nullptr;

    /* Set it to default in case of failure */
    *set = nullptr;

    res = __os_memory_alloc(&stack, THREAD_STACK_SIZE);
    if(res) { return res; }

    stack += THREAD_STACK_SIZE - sizeof(struct os_thread_s);
    disp = (os_tid_t)stack;

    /* Set thread control to defaults */
    disp->ret_val = nullptr;
    /* It will be same for both so does not matter */
    disp->std_funcs.with = func;
    disp->std = std;
    disp->arg = arg;
    disp->tid = 0;

    /* RDI = THREAD_FLAGS */
    /* RSI = disp */
    /* RDX = parent_tid */
    /* RCX = child_tid */
    /* Non returning for child thread */
    ret = __thread_clone_linux(THREAD_FLAGS, disp, &disp->tid, &disp->tid);

    if(0 > ret && ret > -MAX_ERRNO) {
        res = __os_error_map(ret);
        __os_memory_free(&stack, THREAD_STACK_SIZE);
    }

    *set = disp;
    return res;
}

#else /* End - SYS_OS_LINUX */
#error "The current platform does not have a backend yet!"
#endif /* SYS_OS */
