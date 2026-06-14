#include "memory_private.h"

error_t allocator_free_pointer
(allocator_t* alloc, void* set)
{
    /* Init variables */
    u8* ptr = 0;
    heap_header_t* header = 0;
    u32 total = 0;
    error_t res = success;

    /* Check inputs */
    if(!set || !alloc) { return null_pointer; }
    ptr = *(void**)set;
    if(!ptr) { return success; }

    /* Skip to header and one for first null byte */
    header = ((heap_header_t*)(uintptr_t)ptr - 1);

    res = __validate_header(header);
    if(res == invalid_pointer) { return res; }
    else if (res == heap_underflow)
    { header->alloc->meta.underflow(header->alloc, header); }
    else if (res == heap_overflow)
    { header->alloc->meta.overflow(header->alloc, header); }

    total = ALIGN_64(header->wanted_alloc + ADDITIONAL_HEADER_SIZE);

    mutex_lock(&alloc->meta.mutex);

    if(total < RAW_ALLOCATION_THRESHOLD) {
        /* Set free small chunk to zero*/
        __set_chunks_free(alloc->free_bits, header->idx, total / CHUNK_SIZE);

        /* Zero the user's pointer */
        *(void**)set = 0;
        /* Result is already success but we reassign it for
         * safety in case the logic changes later
         */
        res = success;
        goto end;
    }

    alloc->headers[header->idx] = nullptr;

    /* If we cant free any memory just stop and return an error */
    if(0 != syscall_2_linux(syscall_munmap, (ssize_t)header, total)) {
        alloc->headers[header->idx] = header;
        res = memory_error;
        goto end;
    }

    /* Zero the user's pointer */
    *(void**)set = 0;
end:
    mutex_unlock(&alloc->meta.mutex);
    return res;
}
