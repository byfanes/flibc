#include "memory_private.h"
#include "error.h"
#include "syscall.h"

error_t __mem_alloc
(allocator_t* alloc, void* set, usz size, TRACE_ARGS)
{
    /* This is a wrapper function */
    if(!alloc || !alloc->meta.alloc_pointer) { return null_pointer; }
    return alloc->meta.alloc_pointer(alloc, size, set, USE_TRACE_ARGS);
}
