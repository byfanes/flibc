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
        (__os_addr_wake_all_u32(&cond->seq))
    ), res);
}
