#include "memory_private.h"

error_t __mem_calloc
(allocator_t* alloc, void* set, usz size, const char *file_name, u32 line)
{
    /* Init variables */
    error_t res = success;

    return ((void)(
        (res = __mem_alloc(alloc, set, size, file_name, line)) ||
        (res = mem_zeroed_len(*(void**)set, size))
    ), res);
}
