#include "process_private.h"

error_t proc_wait
(da_proc_t* procs)
{
    /* Init variables */
    u32 i = 0;
    error_t res = success;
    error_t out = success;

    /* Check input */
    if(!procs || !procs->items)
    { return null_pointer; }

    for(; i < procs->count; ++i) {
        out = waitapid(procs->items[i].handle);
        if(!res) { res = out; }
    }

    /* Wont give an error because we already use and checked it */
    da_clear(procs);
    return res;
}
