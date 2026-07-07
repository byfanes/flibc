#include "string_private.h"

error_t str_dup
(allocator_t* alloc, str_t* base, str_t* out)
{
    /* Init variables */
    error_t res = success;

    return ((void)(
        /* Validate user input */
        (res = (alloc && base && out) ? success : null_pointer) ||
        /* Reserve a memory */
        (res = str_init(alloc, out, base->count)) ||
        /* Copy the content to memory */
        (res = __str_copy_content(out, base->items, base->count))
    ), res);
}
