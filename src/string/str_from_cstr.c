#include "string_private.h"

fc_error_t str_from_cstr
(str_t* out, const char* cstr)
{
    /* Init variables */
    u32 len = 0;
    fc_error_t res = fce_success;
    slice_t dst = {0}, src = {0};
    
    /* Validate user input */
    if(!out) { return fce_str_from_cstr_out_null; }
    if(!cstr) { return fce_str_from_cstr_cstr_null; }

    /* Len of cstr including null byte */
    while(cstr[len++]);

    /* Reserve a memory */
    res = da_reserve(out, len);
    if(res) { return res; }

    /* Set slices for copying */
    set_slice(&src, cstr, len);
    set_slice(&dst, (*out)->items, len);

    *(u32*)(uintptr_t)&(*out)->count = len - 1;
    
    /* Copy and return the result */
    return memcpy(dst, src);
}
