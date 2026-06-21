#include "memory_private.h"

error_t __mem_alloc_sl
(allocator_t* alloc, void* set, usz el_size, usz n, TRACE_ARGS)
{
    void* ptr = nullptr;
    error_t res = success;

    /* Check inputs */
    if(!set) { return null_pointer; }
    if(!el_size) { return elsize_zero; }

    if((res = __mem_alloc(alloc, &ptr, el_size * n, USE_TRACE_ARGS))) { return res; }

    return slice_set(set, ptr, n);
}
