#include "threads_private.h"

error_t thread_create_std
(thread_t *thread, void *(*func)(std_t *, void *), std_t *std, void *arg)
{
    /* Init variables */
    error_t res = success;

    return ((void)(
        /* Check inputs */
        (res = (thread && std && func) ? success : null_pointer) ||
        /* Call thread new to handle rest of the execution */
        (res = __os_thread_new(&thread->opaque, func, std, arg))
    ), res);
}
