#include "memory_private.h"

error_t allocator_alloc_pointer
(allocator_t* alloc, usize_t n, void* set, const char* file_name, usize_t line)
{
    /* Init variables */
    usize_t needed = 0, chunk_count = 0;
    u32 idx = 0, node_idx = 0;
    u8* ptr = 0;
    heap_header_t* header = 0;
    heap_node_t node = {0};
    error_t res = success;

    /* Check input */
    if(!alloc || !set) { return null_pointer; }

    /* usize_t is for end null bytes and align it */
    needed = (n + sizeof(heap_header_t) + sizeof(usize_t));
    needed = ALIGN_64(needed);
    chunk_count = needed / CHUNK_SIZE;

    /* Check for allocations which are bigger than 4 GB (max limit of u32) */
    if(needed > (u32)(-1)) { return exceeding_memory_allocation; }

    /* We got a request which is greater than threshold */
    if (needed >= (ALLOCATION_SIZE / 16)) {
        for(; node_idx < ALLOCATOR_NODE_COUNT; ++node_idx) {
            if(alloc->nodes[node_idx].type == heap_node_empty) {
                goto found;
            }
        }

        if(alloc->next) {
            /* If there is a next allocator try to use it */
            return alloc->alloc_pointer(alloc->next, n, set, file_name, line);
        }
        /* If there is not a next allocator create it and use it */
        if((res = alloc->init(&alloc->next))) { return res; }
        /* Set flags from previous allocator*/
        if((res = allocator_set_flags(alloc->next, alloc->flags))) { return res; }
        /* If there is a next allocator try to use it */
        return alloc->alloc_pointer(alloc->next, n, set, file_name, line);
found:
        /* Call syscall for new chunk memory */
        ptr = (u8*)syscall_6_linux(syscall_mmap, 0, (ssize_t)needed,
        (PROT_READ|PROT_WRITE), (MAP_PRIVATE|MAP_ANONYMOUS), (ssize_t)(-1), 0);

        /* Error check */
        if(!ptr || ptr == MMAP_FAILED) { return memory_error; }

        /* Set node and assign it */
        node.start = ptr;
        node.type = raw_chunk_allocation;
        alloc->nodes[node_idx] = node;
    } else {
        /* We are making an allocation which is less than threshold
         * which will be (probably) easier to fit in the chunks
         */

        /* Check for bits */
        idx = __find_free_chunks(alloc->free_bits, CHUNK_MAX, (u32)chunk_count);

        if(idx == CHUNK_IDX_FAILED) {
            if(alloc->next) {
                /* If there is a next allocator try to use it */
                return alloc->alloc_pointer(alloc->next, n, set, file_name, line);
            }
            /* If there is not a next allocator create it and use it */
            if((res = alloc->init(&alloc->next))) { return res; }
            /* Set flags from previous allocator*/
            if((res = allocator_set_flags(alloc->next, alloc->flags))) { return res; }
            /* If there is a next allocator try to use it */
            return alloc->alloc_pointer(alloc->next, n, set, file_name, line);
        }

        /* Mark them as they are part of the memory */
        __set_chunks_used(alloc->free_bits, idx, (u32)chunk_count);

        /* Get the pointer */
        ptr = ((u8*)alloc + sizeof(allocator_t) + CHUNK_SIZE * idx);
    }

    /* Set header */
    header = (heap_header_t*)(uintptr_t)ptr;
    header->alloc = alloc;
    /* Allocated more than 4GB is prohibited and checked before */
    header->req_alloced = (u32)n;
    header->raw_alloced = (u32)needed;
    /* idx are in range 0 to 16387 check allocator_t definition */
    header->chunk_idx = (u16)idx;
    header->file_name = file_name;
    /* It is safe case a file should not have more line than
     * 4B if it has it is not my problem
     */
    header->line = (u32)line;
    header->first_null = 0;
    header->is_raw_chunk = (needed >= (ALLOCATION_SIZE / 16));

    /* Last null byte */
    *(usize_t*)(uintptr_t)(ptr + sizeof(heap_header_t) + n) = 0;

    /* Set user's pointer */
    *(void**)set = (ptr + sizeof(heap_header_t));

    return success;
}
