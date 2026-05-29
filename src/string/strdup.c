#include "string_private.h"

error_t strdup
(allocator_t* alloc, str_t* base, str_t* out)
{
    /* Init variables */
    error_t res = success;

    /* Validate user input */
    if(!alloc || !base || !out) { return null_pointer; }

    /* Reserve a memory */
    if((res = str_init(alloc, out, base->count))) { return res; }

    return __str_copy_content(out, base->items, base->count);
}
