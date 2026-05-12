#include "memory_private.h"
#include "error.h"
#include "syscall.h"

fc_error_t calloc
(allocator_t* alloc, usize_t size, void* set)
{
    /* Init variables */
    fc_error_t res = fce_success;
    slice(u8) sl = {0};

    /* Allocate memory - User input validation done here */
    if((res = malloc(alloc, size, set))) { return res; }

    /* Set slice and zero the bytes.
     * Arguments are should be valid in here because size zero is allowed
     * and there will be allways a pointer too otherwise it means malloc fails
     * and we dont reach here
     */
    set_slice(&sl, *(void**)set, size);
    return memset(&sl, 0);
}
