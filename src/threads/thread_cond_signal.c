#include "threads_private.h"

error_t thread_cond_signal
(thread_cond_t* cond)
{
    /* Init variables */
    error_t res = success;

    return ((void)(
        /* Check inputs */
        (res = (cond) ? success : null_pointer) ||
        /* Add to the seq */
        (atomic_fetch_add_u32(&cond->seq, 1), success) ||
        /* Signal a thread */
        (res = (0 > syscall_6_linux(syscall_futex, (ssize_t)&cond->seq, FUTEX_WAKE, 1, 0, 0, 0))
             ? thread_cond_error : success)
    ), res);
}
