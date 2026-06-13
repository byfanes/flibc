#include "threads_private.h"

error_t thread_join_da
(da_thread_t* threads, da_retval_t* ret_vals)
{
    /* Init variables */
    error_t res = success;
    void* ret_val = 0;
    u32 i = 0;

    /* Check inputs */
    if(!threads || !threads->items || !ret_vals || !ret_vals->items)
    { return null_pointer; }

    /* Zero the item count */
    set_slice(ret_vals, ret_vals->items, 0);
    /* Grow if it needs more */
    if(ret_vals->capacity < threads->capacity) {
        if((res = da_grow(ret_vals, threads->capacity - ret_vals->capacity)))
        { return res; }
    }

    /* Iterate over all of the thread it might be slow because we wait on a
     * thread rather than skipping it and checking next one and coming back
     */
    for(; i < threads->count; ++i) {
        /* Join the thread */
        if((res = thread_join(&threads->items[i], &ret_val)))
        { return res; }
        /* Set return value */
        ret_vals->items[i] = ret_val;
    }

    return res;
}
