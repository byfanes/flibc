#include "string_private.h"

error_t str_from_cstr
(allocator_t* alloc, str_t* out, const char* cstr)
{
    /* Init variables */
    usz len = 0;
    error_t res = success;

    return ((void)(
        /* Validate user input */
        (res = (alloc && out && cstr) ? success : null_pointer) ||
        /* Get the size of current string without null byte */
        (len = cstr_len(cstr), success) ||
        /* Allocate new string with that size */
        (res = str_init(alloc, out, len)) ||
        /* Copy the contents of cstr to string */
        (res = __str_copy_content(out, cstr, len))
     ), res);
}
