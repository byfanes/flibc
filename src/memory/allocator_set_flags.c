#include "memory_private.h"

error_t allocator_set_flags
(allocator_t* alloc, u32 flags)
{
    error_t res = success;

    /* TODO: we can add some checking for allocator flags */
    if(!alloc) { return null_pointer; }
    mutex_lock(&alloc->meta.mutex);

    alloc->meta.flags = flags;
    if(alloc->meta.next) { res = allocator_set_flags(alloc->meta.next, flags); }

    mutex_unlock(&alloc->meta.mutex);
    return res;
}
