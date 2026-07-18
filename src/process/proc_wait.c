#include "process_private.h"

error_t proc_wait
(da_proc_t *procs, da_ssz_t *codes)
{
    /* Init variables */
    u32 i = 0;
    error_t res = success, cur_res = success;
    ssz tmp = 0;

    /* Check input */
    if(!procs || !procs->items)
    { return null_pointer; }

    if(codes && codes->items) {
        for(; i < procs->count; ++i) {
            cur_res = __os_process_wait(procs->items[i], codes->items + i);
            res = res ? res : cur_res;
        }
    } else {
        for(; i < procs->count; ++i) {
            cur_res = __os_process_wait(procs->items[i], &tmp);
            res = res ? res : cur_res;
        }
    }

    /* Wont give an error because we already use and checked it */
    da_clear(procs);
    return res;
}
