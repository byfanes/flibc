#include "string_private.h"

error_t strdup
(allocator_t* alloc, str_t* base, str_t* out)
{
    /* Init variables */
    error_t res = success;
    slice(u8) src = {0};

    /* Validate user input */
    if(!alloc || !base || !out) { return null_pointer; }

    /* Reserve a memory */
    if((res = str_init(alloc, out, base->count))) { return res; }

    /* Set slices for copying */
    set_slice(&src, base->items, base->count);

    return __str_copy_content(out, src);
}
