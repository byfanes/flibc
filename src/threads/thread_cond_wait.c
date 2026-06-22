#include "threads_private.h"

error_t thread_cond_wait
(thread_cond_t* cond, mutex_t* mutex)
{
    /* Init variables */
    u32 current_seq = 0;
    error_t res = success;
    ssz ret = 0;
    
    /* Check inputs */
    if (!cond || !mutex) { return null_pointer; }

    /* Get current state */
    current_seq = atomic_load_u32(&cond->seq);
    /* Allow other threads to work */
    if((res = mutex_unlock(mutex))) { return res; }

    /* Goto thread sleep */
    ret = syscall_6_linux(syscall_futex, (ssize_t)&cond->seq, FUTEX_WAIT, current_seq, 0, 0, 0);

    /* Wake up again */
    if((res = mutex_lock(mutex))) { return res; }

    if(ret < 0) { return thread_cond_error; }
    return res;
}
