#include "string_private.h"

error_t str_from_cstr
(allocator_t* alloc, str_t* out, const char* cstr)
{
    /* Init variables */
    usz len = 0;
    error_t res = success;

    /* Validate user input */
    if(!alloc || !out || !cstr) { return null_pointer; }

    /* Len of cstr including null byte */
    len = cstr_len(cstr);

    /* Reserve a memory */
    if((res = str_init(alloc, out, len))) { return res; }

    /* Copy and return the result */
    return __str_copy_content(out, cstr, len);
}
