#include "memory_private.h"

error_t __validate_header
(heap_header_t* header)
{
    u8 i = 0;
    usz null = 0;
    bool is_null = false;

    /* Nullptr */
    if(!header) { return invalid_pointer; }

    /* We give aligned pointer so we expect aligned pointer */
    if((uintptr_t)header % 16 != 0) { return invalid_pointer; }

    if(!header->alloc) { return invalid_pointer; }

    for(; i < sizeof(header->safety); ++i)
    {
        if(header->safety[i] != 'A' + i) {
            header->alloc->meta.overflow(header->alloc, header);
            /* should be dead end */
            return heap_underflow;
        }
    }
    if(header->first_null != 0) {
        header->alloc->meta.underflow(header->alloc, header);
        /* should be dead end */
        return heap_underflow;
    }

    mem_cmp_raw(((u8*)(header + 1) + header->wanted_alloc), &null, sizeof(null), &is_null);
    if(!is_null) {
        header->alloc->meta.overflow(header->alloc, header);
        /* should be dead end */
        return heap_underflow;
    }

    return success;
}
