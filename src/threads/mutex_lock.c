#include "threads_private.h"

error_t mutex_lock(mutex_t* mutex)
{
    if(!mutex) { return null_pointer; }

    if(atomic_cas_i32(&mutex->state, 0, 1)) { 
        return success; 
    }

    while(atomic_xchg_i32(&mutex->state, 2) != 0) {
        syscall_6_linux(syscall_futex, (ssz)&mutex->state, FUTEX_WAIT, 2, 0, 0, 0);
    }

    return success;
}
