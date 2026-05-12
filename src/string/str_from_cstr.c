#include "string_private.h"

fc_error_t str_from_cstr
(allocator_t* alloc, str_t* out, const char* cstr)
{
    /* Init variables */
    u32 len = 0;
    fc_error_t res = fce_success;
    slice(u8) src = {0};

    /* Validate user input */
    if(!alloc || !out || !cstr) { return fce_null_pointer; }

    /* Len of cstr including null byte */
    while(cstr[len++]);
    len--;

    /* Reserve a memory */
    res = str_init(alloc, out, len);
    if(res) { return res; }

    /* Set slices for copying */
    set_slice(&src, cstr, len);

    /* Copy and return the result */
    return __str_copy_content(out, src);
}
