#include "threads_private.h"

error_t mutex_unlock(mutex_t* mutex)
{
    if(!mutex) { return null_pointer; }

    if(atomic_fetch_sub_i32(&mutex->state, 1) == 1) { 
        return success; 
    }

    mutex->state = 0;
    __os_addr_wake_i32(&mutex->state);

    return success;
}
