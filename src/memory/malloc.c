#include "memory_private.h"
#include "error.h"
#include "syscall.h"

fc_error_t __malloc
(allocator_t* alloc, usize_t size, void* set, TRACE_ARGS)
{
    /* This is a wrapper function */
    return allocator_alloc_pointer(alloc, size, set, USE_TRACE_ARGS);
}
