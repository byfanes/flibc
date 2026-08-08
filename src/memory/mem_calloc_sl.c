#include "memory_private.h"

error_t __mem_calloc_sl
(allocator_t* alloc, void* set, usz el_size, usz n, const char *file_name, u32 line)
{
    void* ptr = nullptr;
    error_t res = success;

    return ((void)(
        (res = (set) ? success : null_pointer) ||
        (res = (el_size) ? success : elsize_zero) ||
        (res = __mem_calloc(alloc, &ptr, el_size * n, file_name, line)) ||
        (res = slice_set(set, ptr, n))
    ), res);
}
