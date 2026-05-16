#include "memory_private.h"

error_t allocator_alloc_pointer
(allocator_t* alloc, usize_t n, void* set, const char* file_name, usize_t line)
{
    /* Init variables */
    usize_t needed = 0, chunk_count = 0;
    u32 idx = 0;
    u8* ptr = 0;
    heap_header_t* header = 0;

    /* Check input */
    if(!alloc || !set) { return null_pointer; }

    /* u16 is for end null bytes and align it */
    needed = (n + sizeof(heap_header_t) + sizeof(u16));
    needed = ALIGN_64(needed);
    chunk_count = needed / CHUNK_SIZE;

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
    /* Allocated more than 4GB is prohibited */
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

    /* Last null byte */
    *(u16*)(uintptr_t)(ptr + sizeof(heap_header_t) + n) = 0;

    /* Set user's pointer one for first null byte */
    *(void**)set = (ptr + sizeof(heap_header_t));

    return success;
}
