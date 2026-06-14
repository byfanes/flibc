#include "string_private.h"

error_t str_init
(allocator_t* alloc, str_t* out, usz amount)
{
    /* This is a wrapper function */
    return da_init(alloc, out, amount);
}

