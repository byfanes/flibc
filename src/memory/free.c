#include "memory_private.h"
#include "error.h"
#include "syscall.h"

error_t free
(void* set)
{
    /* This is wrapper function but its getting allocator by pointer */
    /* Init variables */
    allocator_t* alloc = 0;

    /* Check inputs */
    if(!set) { return null_pointer; }
    if(!*(void**)set) { return success; }

    /* Get allocator */
    if(allocator_get_from_ptr(*(void**)set, &alloc)) { return invalid_pointer; }

    /* Allocator free */
    return allocator_free_pointer(alloc, set);
}
