#include "memory_private.h"

error_t allocator_set_flags
(allocator_t* alloc, u32 flags)
{
    /* TODO: we can add some checking for allocator flags */
    if(!alloc) { return null_pointer; }
    alloc->flags = flags;
    if(alloc->next) { return allocator_set_flags(alloc->next, flags); }
    return success;
}
