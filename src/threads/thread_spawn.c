#include "threads_private.h"

error_t thread_spawn
(allocator_t* alloc, da_thread_t* threads, void*(*func)(void*), void* arg)
{
    /* Init variables */
    error_t res = success;

    /* It will check for the threads and threads' items and allocated a new place for the thread */
    if((res = da_grow_if(threads, 1))) { return res; }

    /* It will check for alloc and func and create a new thread */
    if((res = thread_create(alloc, threads->items + threads->count, func, arg))) { return res; }

    /* Push the new thread - its already allocated so we just increase the count */
    return slice_set(threads, threads->items, threads->count + 1);
}
