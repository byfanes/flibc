#include "memory_private.h"


fc_error_t allocator_get_from_ptr
(void* ptr, allocator_t** set)
{
    /* Init variables */
    heap_header_t* header = 0;
    u32 max_count = 0;

    /* One byte is null byte so skip that*/
    header = ((heap_header_t*)ptr - 1);

    /* Check for if the chunk amount covers that much space */
    max_count = header->chunk_count * CHUNK_SIZE;
    if(header->raw_alloced > max_count)
    { return fce_invalid_pointer; }

    /* Req alloced should be less than max because we add header and two null bytes */
    if(header->req_alloced + sizeof(heap_header_t) + sizeof(u16) > max_count)
    { return fce_invalid_pointer; }

    /* Raw alloced is aligned to 64(CHUNK_SIZE) */
    if(header->raw_alloced & (CHUNK_SIZE - 1))
    { return fce_invalid_pointer; }

    /* Header should be allign to chunks' begining */
    *set = (allocator_t*)(((u8*)header - header->chunk_idx * CHUNK_SIZE) - sizeof(allocator_t));

    return fce_success;
}
