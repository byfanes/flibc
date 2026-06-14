#include "memory_private.h"

static void set_header
(allocator_t* alloc, void** set, void* ptr, u32 n, u16 idx, const char* file_name, u32 line)
{
    heap_header_t* header = 0;
    u8 i = 0;

    /* Set Header */
    header = (heap_header_t*)ptr;
    header->alloc = alloc;
    header->file_name = file_name;
    /* It is safe case a file should not have more line than
    * 4B if it has it is not my problem
    */
    header->line = line;
    header->wanted_alloc = n;
    header->idx = idx;
    /* Add safety to here */
    header->first_null = 0;

    /* Compiler will unroll it */
    for(; i < sizeof(header->safety); ++i)
    { header->safety[i] = 'A' + (u8)i; }

    /* Last null byte */
    *(usz*)(uintptr_t)((u8*)ptr + sizeof(heap_header_t) + n) = 0;

    /* Set users pointer too */
    *set = header + 1;
}

static error_t alloc_big_chunk
(allocator_t* alloc, u32 n, u32 chunk_count, void* set, const char* file_name, u32 line)
{
    /* Header idx is 0 to 248 - 504 (depending on arch) */
    u16 header_idx = 0;
    u8* ptr = 0;
    error_t res = success;

    for(; header_idx < ALLOCATOR_HEADER_COUNT; ++header_idx) {
        if(!alloc->headers[header_idx]) {
            /* Call syscall for new chunk memory */
            ptr = (u8*)syscall_6_linux(syscall_mmap, 0, chunk_count * CHUNK_SIZE,
            (PROT_READ|PROT_WRITE), (MAP_PRIVATE|MAP_ANONYMOUS), (ssz)(-1), 0);

            /* Error check */
            if(!ptr || ptr == MMAP_FAILED) { return memory_error; }

            /* Set header pointer to allocator too */
            alloc->headers[header_idx] = (heap_header_t*)(uintptr_t)ptr;

            /* Set header */
            set_header(alloc, set, ptr, n, header_idx, file_name, line);
            return res;
        }
    }

    if(alloc->meta.next) {
        /* If there is a next allocator try to use it */
        return alloc->meta.alloc_pointer(alloc->meta.next, n, set, file_name, line);
    }

    /* If there is not a next allocator create it and use it */
    if((res = alloc->meta.init(&alloc->meta.next))) { return res; }

    /* Set flags from previous allocator*/
    if((res = allocator_set_flags(alloc->meta.next, alloc->meta.flags))) { return res; }

    /* If there is a next allocator try to use it */
    return alloc->meta.alloc_pointer(alloc->meta.next, n, set, file_name, line);
}

static error_t alloc_small_chunk
(allocator_t* alloc, u32 n, u32 chunk_count, void* set, const char* file_name, u32 line)
{
    /* Init variables */
    u32 idx = 0;
    error_t res = success;
    u8* ptr = 0;

    /* Check for bits */
    idx = __find_free_chunks(alloc->free_bits, CHUNK_MAX, chunk_count);

    if(idx == CHUNK_IDX_FULL) {
        if(alloc->meta.next) {
            /* If there is a next allocator try to use it */
            return alloc->meta.alloc_pointer(alloc->meta.next, n, set, file_name, line);
        }

        /* If there is not a next allocator create it and use it */
        if((res = alloc->meta.init(&alloc->meta.next))) { return res; }

        /* Set flags from previous allocator*/
        if((res = allocator_set_flags(alloc->meta.next, alloc->meta.flags))) { return res; }

        /* If there is a next allocator try to use it */
        return alloc->meta.alloc_pointer(alloc->meta.next, n, set, file_name, line);
    }

    /* Mark them as they are part of the memory */
    __set_chunks_used(alloc->free_bits, idx, (u32)chunk_count);

    /* Get the pointer */
    ptr = ((u8*)alloc + sizeof(allocator_t) + CHUNK_SIZE * idx);

    /* Set header */
    /* safe to cast idx to u16
     * idx are in range 0 to 16387 check allocator_t definition
     */
    set_header(alloc, set, ptr, n, (u16)idx, file_name, line);

    return success;
}

error_t allocator_alloc_pointer
(allocator_t* alloc, usz n, void* set, const char* file_name, u32 line)
{
    /* Init variables */
    usz needed = 0, chunk_count = 0;
    error_t res = success;
    
    /* Check input */
    if(!alloc || !set) { return null_pointer; }

    /* usz is for end null bytes and align it */
    needed = (n + sizeof(heap_header_t) + sizeof(usz));
    needed = ALIGN_64(needed);
    chunk_count = needed / CHUNK_SIZE;

    /* Check for allocations which are bigger than 4 GB (max limit of u32) */
    /* Allocated more than 4GB is prohibited */
    if(needed > (u32)(-1)) { return exceeding_memory_allocation; }

    mutex_lock(&alloc->meta.mutex);
    
    /* We got a request which is greater than threshold */
    if (needed >= RAW_ALLOCATION_SIZE) {
        res = alloc_big_chunk(alloc, (u32)n, (u32)chunk_count, set, file_name, (u32)line);
        goto end;
    }
    /* We are making an allocation which is less than threshold
     * which will be (probably) easier to fit in the chunks
     */
    res = alloc_small_chunk(alloc, (u32)n, (u32)chunk_count, set, file_name, (u32)line);

end:
    mutex_unlock(&alloc->meta.mutex);
    return res;
}
