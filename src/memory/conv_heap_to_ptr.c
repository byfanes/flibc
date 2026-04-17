#include "memory.h"

def_slice_t conv_heap_to_ptr
(void* ptr)
{
    heap_header_t* head = 0;
    uint8_t* bptr = 0;
    memcpy_sized(&head,ptr,sizeof(void*));
    memcpy_sized(&bptr,ptr,sizeof(void*));
    head -= 1;
    return (def_slice_t){ .base = bptr, .count = head->alloced };
}
