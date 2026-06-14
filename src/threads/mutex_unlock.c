#include "threads_private.h"

error_t mutex_unlock(mutex_t* mutex)
{
    if(!mutex) { return null_pointer; }

    if(atomic_fetch_sub_i32(&mutex->state, 1) == 1) { 
        return success; 
    }

    mutex->state = 0;
    syscall_6_linux(syscall_futex, (ssz)&mutex->state, FUTEX_WAKE, 1, 0, 0, 0);

    return success;
}
