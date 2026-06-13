#include "threads_private.h"

error_t thread_spawn_std
(std_t* std, da_thread_t* threads, void*(*func)(std_t*, void*), void* arg)
{
    /* Init variables */
    thread_t t = {0};
    error_t res = success;

    /* Check thread da because if we after check it we might have dangling thread */
    if(!threads || !threads->items) { return null_pointer; }
    /* Create a thread with std */
    if((res = thread_create_std(std, &t, func, arg))) { return res; }
    /* Push the new thread */
    return da_push(threads, &t);
}
