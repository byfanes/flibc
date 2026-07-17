#include "memory_private.h"

error_t allocator_init
(allocator_t** set)
{
    /* Init variables */
    allocator_t* alloc = 0;
    error_t res = success;

    /* Check input */
    if(!set) { return null_pointer; }

    res = __os_memory_alloc(&alloc, RAW_ALLOCATION_SIZE);
    if(res) { return res; }

    /* Zero-ed the struct so bitfields are zero now */
    mem_zeroed(alloc);

    /* This is an default allocator so we can use default functions */
    alloc->meta.alloc_pointer = allocator_alloc_pointer;
    alloc->meta.free_pointer = allocator_free_pointer;
    alloc->meta.init = allocator_init;
    alloc->meta.deinit = allocator_deinit;
    alloc->meta.overflow = allocator_overflow;
    alloc->meta.underflow = allocator_underflow;
    alloc->meta.mutex.state = 0;
    alloc->meta.next = 0;

    *set = alloc;

    return success;
}
