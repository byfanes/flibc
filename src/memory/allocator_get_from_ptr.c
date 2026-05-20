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

    /* One byte is null byte so skip that*/
    header = ((heap_header_t*)ptr - 1);

    if(!__validate_header(header)) { return invalid_pointer; }

    *set = header->alloc;

    return success;
}
