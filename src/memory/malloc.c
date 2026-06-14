#include "memory_private.h"
#include "error.h"
#include "syscall.h"

error_t __malloc
(allocator_t* alloc, usize_t size, void* set, TRACE_ARGS)
{
    /* This is a wrapper function */
    if(!alloc || !alloc->meta.alloc_pointer) { return null_pointer; }
    return alloc->meta.alloc_pointer(alloc, size, set, USE_TRACE_ARGS);
}
