#include "threads_private.h"

error_t thread_join
(thread_t* thread, void** _Nullable ret_val)
{
    /* Init variables */
    void *tmp = 0;

    /* Check thread pointer */
    if(!thread) { return null_pointer; }

    /* Pass to os layer to handle the rest and set a valid pointer for return */
    return __os_thread_join(&thread->opaque, (ret_val) ? ret_val : &tmp);
}
