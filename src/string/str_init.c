#include "string_private.h"

fc_error_t str_init
(allocator_t* alloc, str_t* out, usize_t amount)
{
    /* This is a wrapper function */
    return da_init(alloc, out, amount);
}

