#include "threads_private.h"

error_t thread_cond_signal
(thread_cond_t* cond)
{
    /* Init variables */
    ssz ret = 0;

    /* Check inputs */
    if (!cond) { return null_pointer; }

    /* Add to the seq */
    atomic_fetch_add_u32(&cond->seq, 1);

    /* Signal a thread */
    ret = syscall_6_linux(syscall_futex, (ssize_t)&cond->seq, FUTEX_WAKE, 1, 0, 0, 0);
    if(ret < 0) {
        return thread_cond_error;
    }

    return success;
}
