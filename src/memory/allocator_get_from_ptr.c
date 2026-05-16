#include "memory_private.h"


fc_error_t allocator_get_from_ptr
(void* ptr, allocator_t** set)
{
    /* Init variables */
    heap_header_t* header = 0;

    /* One byte is null byte so skip that*/
    header = ((heap_header_t*)ptr - 1);

    if(!__validate_header(header)) { return fce_invalid_pointer; }

    /* Header should be allign to chunks' begining */
    *set = (allocator_t*)(((u8*)header - header->chunk_idx * CHUNK_SIZE) - sizeof(allocator_t));

    return fce_success;
}
