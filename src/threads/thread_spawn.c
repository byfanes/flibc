#include "threads_private.h"

error_t thread_spawn
(da_thread_t *threads, f_thread_func func, void *arg)
{
    /* Init variables */
    error_t res = success;

    return ((void)(
        /* Alloc a free scape for the new thread order matters because we might have dangling thread then */
        (res = da_grow_if(threads, 1)) ||
        /* Create the new thread to new location */
        (res = thread_create(threads->items + threads->count, func, arg)) ||
        /* Update the count of dynamic array */
        (res = slice_set(threads, threads->items, threads->count + 1)))
    , res);
}
