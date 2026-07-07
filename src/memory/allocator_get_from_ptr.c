#include "memory_private.h"

/* Right now this function is redundant because we already store
 * allocator point in side of the header so the only use case for
 * this not breaking other functions and validating header
 */
error_t allocator_get_from_ptr
(void* ptr, allocator_t** set)
{
    /* Init variables */
    error_t res = success;
    heap_header_t* header = ((heap_header_t*)ptr - 1);

    return ((void)(
        (res = (ptr) ? success : null_pointer) ||
        (res = __validate_header(header)) ||
        (*set = header->alloc, success)
    ), res);
}
