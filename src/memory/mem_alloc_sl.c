#include "memory_private.h"

error_t __mem_alloc_sl
(allocator_t* alloc, void* set, usz el_size, usz n, TRACE_ARGS)
{
    void* ptr = nullptr;
    error_t res = success;

    return ((void)(
        (res = (set) ? success : null_pointer) ||
        (res = (el_size) ? success : elsize_zero) ||
        (res = __mem_alloc(alloc, &ptr, el_size * n, USE_TRACE_ARGS)) ||
        (res = slice_set(set, ptr, n))
    ), res);
}
