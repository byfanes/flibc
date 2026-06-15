#include "threads_private.h"

error_t thread_cond_broadcast
(thread_cond_t* cond)
{
    /* Init variables */
    ssz ret = 0;

    /* Check inputs */
    if (!cond) { return null_pointer; }

    /* Add to the seq */
    atomic_fetch_add_u32(&cond->seq, 1);

    /* Broadcast the seq - 0x7FFFFFFF is int max which is maxium possible thread count */
    ret = syscall_6_linux(syscall_futex, (ssize_t)&cond->seq, FUTEX_WAKE, 0x7FFFFFFF, 0, 0, 0);

    if(ret < 0 && (ret == -EINTR || ret == -EAGAIN)) {
        return thread_cond_error;
    }
    
    return success;
}
