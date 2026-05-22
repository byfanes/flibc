#include "memory_private.h"

error_t allocator_free_pointer
(allocator_t* alloc, void* set)
{
    /* Init variables */
    u8* ptr = 0;
    heap_header_t* header = 0;
    u32 i = 0;

    /* Check inputs */
    if(!set || !alloc) { return null_pointer; }
    ptr = *(void**)set;
    if(!ptr) { return success; }

    /* Skip to header and one for first null byte */
    header = ((heap_header_t*)(uintptr_t)ptr - 1);

    if(!__validate_header(header)) { return invalid_pointer; }

    if(!header->is_raw_chunk) {
        /* Set free small chunk to zero*/
        __set_chunks_free(alloc->free_bits, header->chunk_idx, header->raw_alloced / CHUNK_SIZE);

        /* Zero the user's pointer */
        *(void**)set = 0;
        return success;
    }

    /* Find the node of the chunk back */
    for(; i < ALLOCATOR_NODE_COUNT; ++i) {
        if(alloc->nodes[i].start == header) {
            alloc->nodes[i].type = heap_node_empty;
            alloc->nodes[i].start = nullptr;

            /* If we cant free any memory just stop and return an error */
            if(0 != syscall_2_linux(syscall_munmap, header, header->raw_alloced))
            { return memory_error; }

            /* Zero the user's pointer */
            *(void**)set = 0;
            return success;
        }
    }
    return invalid_pointer;
}
