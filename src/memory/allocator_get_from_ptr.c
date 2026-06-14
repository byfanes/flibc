#include "memory_private.h"

/* Right now this function is redundant because we already store
 * allocator point in side of the header so the only use case for
 * this not breaking other functions and validating header
 */
error_t allocator_get_from_ptr
(void* ptr, allocator_t** set)
{
    /* Init variables */
    heap_header_t* header = 0;
    error_t res = success;
    
    /* One byte is null byte so skip that*/
    header = ((heap_header_t*)ptr - 1);

    res = __validate_header(header);
    if(res == invalid_pointer) { return res; }
    else if (res == heap_underflow)
    { header->alloc->meta.underflow(header->alloc, header); }
    else if (res == heap_overflow)
    { header->alloc->meta.overflow(header->alloc, header); }

    *set = header->alloc;

    return success;
}
