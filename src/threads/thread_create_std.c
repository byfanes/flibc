#include "threads_private.h"

error_t thread_create_std
(std_t* std, thread_t* thread, void*(*func)(std_t*, void*), void* _Nullable arg)
{
    /* Init variables */
    u8* stack_ptr = nullptr;
    error_t res = success;

    return ((void)(
        /* Check inputs */
        (res = (thread && std && func) ? success : null_pointer) ||
        /* Allocate stack memory */
        (res = mem_alloc(std->alloc, &stack_ptr, THREAD_STACK_SIZE)) ||
        /* Call thread new to handle rest of the execution */
        (res = __thread_new(stack_ptr, thread, func, std, arg))
    ), (void)( /* Cleanup - free if thread_new fails*/
        ((res) ? mem_free(&stack_ptr) : (0))
    ), res);
}
