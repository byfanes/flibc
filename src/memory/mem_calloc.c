#include "memory_private.h"
#include "error.h"
#include "syscall.h"

error_t __mem_calloc
(allocator_t* alloc, void* set, usz size, TRACE_ARGS)
{
    /* Init variables */
    error_t res = success;

    /* Allocate memory - User input validation done here */
    if((res = __mem_alloc(alloc, set, size, USE_TRACE_ARGS))) { return res; }

    /* Set slice and zero the bytes.
     * Arguments are should be valid in here because size zero is allowed
     * and there will be allways a pointer too otherwise it means malloc fails
     * and we dont reach here
     */
    return mem_zeroed_len(*(void**)set, size);
}
