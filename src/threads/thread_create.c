#include "threads_private.h"

error_t thread_create
(thread_t *thread, void *(*func)(void *), void *arg)
{
    /* Init variables */
    error_t res = success;
    /* Change func signature to use in clone function its safe
     * to cast because in assembly it checks from std pointer if
     * its zero it acts like void*(*func)(void*)
     */
    void *(*user_func)(struct std_s *std, void *)
        = (void* (*)(struct std_s *std, void *))(uintptr_t)func;

    return ((void)(
        /* Check inputs - alloc checked in mem_alloc */
        (res = (func && thread) ? success : null_pointer) ||
        /* Call thread new to handle rest of the execution */
        (res = __os_thread_new(&thread->opaque, user_func, nullptr, arg))
    ), res);
}
