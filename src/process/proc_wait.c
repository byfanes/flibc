#include "process_private.h"

error_t proc_wait
(da_proc_t* procs)
{
    /* Init variables */
    u32 i = 0;
    error_t res = success, cur_res = success;

    /* Check input */
    if(!procs || !procs->items)
    { return null_pointer; }

    for(; i < procs->count; ++i) {
        cur_res = waitapid(procs->items[i].handle);
        res = res ? res : cur_res;
    }

    /* Wont give an error because we already use and checked it */
    da_clear(procs);
    return res;
}
