#include "threads_private.h"

error_t thread_create
(allocator_t* alloc, thread_t* thread, void*(*func)(void*), void* arg)
{
    /* Init variables */
    u8* stack_ptr = nullptr;
    error_t res = success;
    /* Change func signature to use in clone function its safe
     * to cast because in assembly it checks from std pointer if
     * its zero it acts like void*(*func)(void*)
     */
    void* (*user_func)(struct std_s* std, void*)
        = (void* (*)(struct std_s* std, void*))(uintptr_t)func;

    return ((void)(
        /* Check inputs - alloc checked in mem_alloc */
        (res = (func && thread) ? success : null_pointer) ||
        /* Allocate stack memory */
        (res = mem_alloc(alloc, &stack_ptr, THREAD_STACK_SIZE)) ||
        /* Call thread new to handle rest of the execution */
        (res = __thread_new(stack_ptr, thread, user_func, nullptr, arg))
    ), (void)( /* Cleanup if thread_new fails free the memory */
        ((res) ? mem_free(&stack_ptr) : (0))
    ), res);
}
