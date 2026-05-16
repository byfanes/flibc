#include "memory_private.h"

fc_error_t allocator_alloc_pointer
(allocator_t* alloc, usize_t n, void* set)
{
    /* Init variables */
    usize_t needed = 0, chunk_count = 0;
    u32 idx = 0;
    u8* ptr = 0;
    heap_header_t* header = 0;

    /* Check input */
    if(!alloc || !set) { return fce_null_pointer; }

    /* u16 is for end null bytes and align it */
    needed = (n + sizeof(heap_header_t) + sizeof(u16));
    needed = (needed + 63) & (u32)(~63);
    chunk_count = needed / CHUNK_SIZE;

    /* TODO Support larger amounts */
    /*if(needed > 4096) { return 1; }*/

    /* Check for bits */
    idx = __find_free_chunks(alloc->free_bits, CHUNK_MAX, (u32)chunk_count);

    /* TODO its full and we need to allcoate more */
    if(idx == CHUNK_IDX_FAILED) { return 1; }

    /* Mark them as they are part of the memory */
    __set_chunks_used(alloc->free_bits, idx, (u32)chunk_count);

    /* Get the pointer */
    ptr = ((u8*)alloc + sizeof(allocator_t) + CHUNK_SIZE * idx);

    /* Set header */
    header = (heap_header_t*)(uintptr_t)ptr;
    header->req_alloced = (u32)n;
    header->raw_alloced = (u32)needed;
    header->chunk_idx = (u16)idx;
    header->chunk_count = (u16)chunk_count;
    header->first_null = 0;

    /* Last null byte */
    *(u16*)(uintptr_t)(ptr + sizeof(heap_header_t) + n) = 0;

    /* Set user's pointer one for first null byte */
    *(void**)set = (ptr + sizeof(heap_header_t));

    return fce_success;
}
