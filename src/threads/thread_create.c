#include "threads_private.h"

error_t thread_create
(allocator_t* alloc, thread_t* thread, void*(*func)(void*), void* arg)
{
    /* Init variables */
    u8* stack_ptr = 0;
    error_t res = success;
    /* Change func signature to use in clone function its safe
     * to cast because in assembly it checks from std pointer if
     * its zero it acts like void*(*func)(void*)
     */
    void* (*user_func)(struct std_s* std, void*) = (uintptr_t)func;

    /* Check inputs */
    if(!thread || !alloc || !func) { return null_pointer; }

    /* Allocate stack memory */
    if((res = malloc(alloc, THREAD_STACK_SIZE, &stack_ptr))) { return res; }

    /* Call thread new to handle rest of the execution */
    return __thread_new(stack_ptr, thread, user_func, nullptr, arg);
}
