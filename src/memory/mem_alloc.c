#include "memory_private.h"

error_t __mem_alloc
(allocator_t* alloc, void* set, usz size, const char *file_name, u32 line)
{
    /* This is a wrapper function */
    return
        (!alloc || !alloc->meta.alloc_pointer) ? null_pointer :
        alloc->meta.alloc_pointer(alloc, size, set, file_name, line);
}
