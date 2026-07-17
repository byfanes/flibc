#include "memory_private.h"

error_t allocator_free_pointer
(allocator_t* alloc, void* set)
{
    /* Init variables */
    u8* ptr = nullptr;
    heap_header_t* header = nullptr;
    u32 total = 0;
    error_t res = success;

    /* Check inputs */
    if(!set || !alloc) { return null_pointer; }
    ptr = *(void**)set;
    if(!ptr) { return success; }

    /* Skip to header and one for first null byte */
    header = ((heap_header_t*)(uintptr_t)ptr - 1);

    /* Check the header is valid */
    if((res = __validate_header(header))) { return res; }

    /* Get the total amount of allocation */
    total = ALIGN_64(header->wanted_alloc + ADDITIONAL_HEADER_SIZE);

    /* Start freeing logic after this part users' pointer is zeroed */
    mutex_lock(&alloc->meta.mutex);
    *(void**)set = nullptr;

    if(total < RAW_ALLOCATION_THRESHOLD) {
        /* Set free small chunk to zero*/
        __set_chunks_free(alloc->free_bits, header->idx, total / CHUNK_SIZE);
    } else {
        /* Free the allocated memory and zero the node in the array */
        res =  __os_memory_free(alloc->headers + header->idx, total);
    }

    mutex_unlock(&alloc->meta.mutex);
    return res;
}
