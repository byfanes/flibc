#include "memory.h"

def_slice_t conv_heap_to_ptr
(void* ptr)
{
    heap_header_t* base = ((heap_header_t*)ptr - 1);
    return (def_slice_t){ .base = (byte_t*)ptr, .len = base->alloced };
}
