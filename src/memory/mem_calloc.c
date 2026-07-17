#include "memory_private.h"

error_t __mem_calloc
(allocator_t* alloc, void* set, usz size, TRACE_ARGS)
{
    /* Init variables */
    error_t res = success;

    return ((void)(
        (res = __mem_alloc(alloc, set, size, USE_TRACE_ARGS)) ||
        (res = mem_zeroed_len(*(void**)set, size))
    ), res);
}
