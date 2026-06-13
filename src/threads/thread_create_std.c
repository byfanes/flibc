#include "threads_private.h"

error_t thread_create_std
(std_t* std, thread_t* thread, void*(*func)(std_t*, void*), void* _Nullable arg)
{
    /* Init variables */
    u8* stack_ptr = 0;
    error_t res = success;

    /* Check inputs */
    if(!thread || !std || !func) { return null_pointer; }

    /* Allocate stack memory */
    if((res = malloc(std->alloc, THREAD_STACK_SIZE, &stack_ptr))) { return res; }

    /* Call thread new to handle rest of the execution */
    return __thread_new(stack_ptr, thread, func, std, arg);
}
