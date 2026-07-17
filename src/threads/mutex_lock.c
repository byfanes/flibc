#include "threads_private.h"

error_t mutex_lock(mutex_t* mutex)
{
    if(!mutex) { return null_pointer; }

    if(atomic_cas_i32(&mutex->state, 0, 1)) { 
        return success; 
    }

    while(atomic_xchg_i32(&mutex->state, 2) != 0) {
        __os_addr_wait_i32(&mutex->state, 2);
    }

    return success;
}
