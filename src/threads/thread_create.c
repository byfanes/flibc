#include "threads_private.h"

error_t thread_create
(thread_t *thread, f_thread_func func, void *arg)
{
    /* Init variables */
    error_t res = success;
    /* Change func signature to use in clone function its safe
     * to cast because in assembly it checks from std pointer if
     * its zero it acts like void*(*func)(void*)
     */
    f_std_thread_func user_func = (f_std_thread_func)(uintptr_t)func;

    return ((void)(
        /* Check inputs - alloc checked in mem_alloc */
        (res = (func && thread) ? success : null_pointer) ||
        /* Call thread new to handle rest of the execution */
        (res = __os_thread_new(&thread->tid, user_func, nullptr, arg))
    ), res);
}
