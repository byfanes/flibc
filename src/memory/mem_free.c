#include "memory_private.h"
#include "error.h"
#include "syscall.h"

error_t mem_free
(void* set)
{
    /* This is wrapper function but its getting allocator by pointer */
    /* Init variables */
    allocator_t* alloc = 0;

    return
        /* Check inputs */
        (!set) ? null_pointer :
        (!*(void**)set) ? success :
        /* Get allocator */
        (allocator_get_from_ptr(*(void**)set, &alloc)) ? invalid_pointer :
        /* Allocator free */
        alloc->meta.free_pointer(alloc, set);
}
