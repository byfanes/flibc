#include "threads_private.h"

error_t thread_cond_wait
(thread_cond_t* cond, mutex_t* mutex)
{
    /* Init variables */
    u32 current_seq = 0;
    error_t res = success;

    return ((void)(
        /* Check inputs */
        (res = (cond && mutex) ? success : null_pointer) ||
        /* Get current state */
        (current_seq = atomic_load_u32(&cond->seq), success) ||
        /* Allow other threads to work */
        (mutex_unlock(mutex),
            /* Goto thread sleep */
            (__os_addr_wait_u32(&cond->seq, current_seq)),
        /* Wake up again */
        mutex_lock(mutex), res)
    ), res);
}
