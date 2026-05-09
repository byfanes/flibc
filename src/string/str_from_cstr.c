#include "string_private.h"

fc_error_t str_from_cstr
(str_t* out, const char* cstr)
{
    /* Init variables */
    u32 len = 0;
    fc_error_t res = fce_success;
    slice_t src = {0};
    
    /* Validate user input */
    if(!out) { return fce_str_from_cstr_out_null; }
    if(!cstr) { return fce_str_from_cstr_cstr_null; }
   
    /* Len of cstr including null byte */
    while(cstr[len++]);
    len--;
    
    /* Reserve a memory */
    res = str_reserve(out, len);
    if(res) { return res; }

    /* Set slices for copying */
    set_slice(&src, cstr, len);

    /* Copy and return the result */
    return str_copy_content(out, src);
}
