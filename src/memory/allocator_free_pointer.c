#include "memory_private.h"

error_t allocator_free_pointer
(allocator_t* alloc, void* set)
{
    /* Init variables */
    u8* range = (u8*)(alloc + 1);
    u8* ptr = 0;
    heap_header_t* header = 0;

    /* Check inputs */
    if(!set || !alloc) { return null_pointer; }
    ptr = *(void**)set;
    if(!ptr) { return success; }

    /* Check range of ptr */
    if(!(range <= ptr && ptr <= range + ALLOCATION_SIZE))
    { return invalid_pointer; }

    /* Skip to header and one for first null byte */
    header = ((heap_header_t*)(uintptr_t)ptr - 1);

    if(!__validate_header(header)) { return invalid_pointer; }

    /* Set free */
    __set_chunks_free(alloc->free_bits, header->chunk_idx, header->raw_alloced / CHUNK_SIZE);

    /* Zero the user's pointer */
    *(void**)set = 0;
    return success;
}
