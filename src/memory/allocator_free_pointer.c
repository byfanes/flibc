#include "memory_private.h"

fc_error_t allocator_free_pointer
(allocator_t* alloc, void* set)
{
    /* Init variables */
    u8* range = (u8*)(alloc + 1);
    u8* ptr = 0;
    heap_header_t* header = 0;
    u32 max_count = 0;

    /* Check inputs */
    if(!set || !alloc) { return fce_null_pointer; }
    ptr = *(void**)set;
    if(!ptr) { return fce_success; }

    /* Check range of ptr */
    if(!(range <= ptr && ptr <= range + ALLOCATION_SIZE))
    { return fce_invalid_pointer; }

    /* Skip to header and one for first null byte */
    header = ((heap_header_t*)(uintptr_t)ptr - 1);

    /* Chech header */
    if(header->chunk_count != header->raw_alloced / CHUNK_SIZE)
    { return fce_invalid_pointer; }

    /* Chech header */
    max_count = header->chunk_count * CHUNK_SIZE;
    if(header->raw_alloced > max_count)
    { return fce_invalid_pointer; }

    /* Chech header */
    if(header->req_alloced + sizeof(heap_header_t) + sizeof(u16) > max_count)
    { return fce_invalid_pointer; }

    /* Chech header */
    if(header->raw_alloced & (CHUNK_SIZE - 1))
    { return fce_invalid_pointer; }

    /* Set free */
    __set_chunks_free(alloc->free_bits, header->chunk_idx, header->chunk_count);

    /* Zero the user's pointer */
    *(void**)set = 0;
    return fce_success;
}
