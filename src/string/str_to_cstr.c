#include "string_private.h"

error_t str_to_cstr
(allocator_t* alloc, str_t* base, char** out)
{
    /* Init variables */
    error_t res = success;

    return ((void)(
        /* Validate user input */
        (res = (alloc && out && base) ? success : null_pointer) ||
        /* Allocate new memory for c-string */
        (res = mem_alloc(alloc, out, base->count + 1)) ||
        /* Copy the data and set last byte to null */
        (res = mem_cpy_raw((*out), base->items, base->count)) ||
        ((*out)[base->count] = 0, success)
    ), (void)( /* Cleanup */
        ((res) ? mem_free(out) : (0))
    ), res);
}
