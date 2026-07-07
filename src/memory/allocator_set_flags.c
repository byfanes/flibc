#include "memory_private.h"

error_t allocator_set_flags
(allocator_t* alloc, u32 flags)
{
    error_t res = success;
    allocator_t* cur_alloc = alloc, *next = nullptr;

    /* TODO: we can add some checking for allocator flags */
    if(!cur_alloc) { return null_pointer; }

    while(cur_alloc) {
        mutex_lock(&cur_alloc->meta.mutex);
        cur_alloc->meta.flags = flags;
        next = alloc->meta.next;
        mutex_unlock(&cur_alloc->meta.mutex);

        cur_alloc = next;
    }

    return res;
}
