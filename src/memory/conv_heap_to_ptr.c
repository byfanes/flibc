#include "memory.h"

ptr_header_t conv_heap_to_ptr
(void* ptr)
{
    heap_header_t* base = (heap_header_t*)((char*)ptr - sizeof(heap_header_t));
    return (ptr_header_t){ .base = ptr, .len = base->alloced };
}
