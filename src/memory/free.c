#include "memory_private.h"
#include "error.h"
#include "syscall.h"

fc_error_t free
(void* set)
{
    /* This is wrapper function but its getting allocator by pointer */
    /* Init variables */
    allocator_t* alloc = 0;

    /* Check inputs */
    if(!set) { return fce_null_pointer; }
    if(!*(void**)set) { return fce_success; }

    /* Get allocator */
    if(allocator_get_from_ptr(*(void**)set, &alloc)) { return fce_invalid_pointer; }

    /* Allocator free */
    return allocator_free_pointer(alloc, set);
}
