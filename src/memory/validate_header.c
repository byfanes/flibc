#include "memory_private.h"

error_t __validate_header
(heap_header_t* header)
{
    u8 i = 0;
    usize_t last_null = 0;

    /* Nullptr */
    if(!header) { return invalid_pointer; }

    /* We give aligned pointer so we expect aligned pointer */
    if((uintptr_t)header % 16 != 0) { return invalid_pointer; }
    
    if(!header->alloc) { return invalid_pointer; }

    for(; i < sizeof(header->safety); ++i)
    { if(header->safety[i] != 'A' + i) { return heap_underflow; } }
    if(header->first_null != 0) { return heap_underflow; }

    last_null = *(usize_t*)(uintptr_t)((u8*)(header + 1) + header->wanted_alloc);
    if(last_null != 0) { return heap_overflow; }

    return success;
}
