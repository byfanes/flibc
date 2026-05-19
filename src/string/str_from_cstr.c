#include "string_private.h"

error_t str_from_cstr
(allocator_t* alloc, str_t* out, const char* cstr)
{
    /* Init variables */
    u32 len = 0;
    error_t res = success;
    slice(u8) src = {0};

    /* Validate user input */
    if(!alloc || !out || !cstr) { return null_pointer; }

    /* Len of cstr including null byte */
    len = strlen(cstr);

    /* Reserve a memory */
    if((res = str_init(alloc, out, len))) { return res; }

    /* Set slices for copying */
    set_slice(&src, cstr, len);

    /* Copy and return the result */
    return __str_copy_content(out, src);
}
