#include "threads_private.h"

error_t thread_cond_broadcast
(thread_cond_t* cond)
{
    /* Init variables */
    error_t res = success;
    
    return ((void)(
        /* Check inputs */
        (res = (cond) ? success : null_pointer) ||
        /* Add to the seq */
        (atomic_fetch_add_u32(&cond->seq, 1), success) ||
        /* Broadcast the seq - 0x7FFFFFFF is int max which is maxium possible thread count */
        (res = (0 > syscall_6_linux(syscall_futex, (ssize_t)&cond->seq, FUTEX_WAKE, 0x7FFFFFFF, 0, 0, 0))
             ? thread_cond_error : success)
    ), res);
}
