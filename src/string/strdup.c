#include "string_private.h"

fc_error_t strdup
(str_t base, str_t* out)
{
    /* Init variables */
    fc_error_t res = fce_success;
    slice_t src = {0};
    struct str_s* s = 0;
    
    /* Validate user input */
    if(!out) { return fce_strdup_out_null; }

    /* Reserve a memory */
    res = str_reserve(out, base.count);
    if(res) { return res; }

    /* Set slices for copying */
    set_slice(&src, base.items, base.count);
    s = (void*)out;
    s->count = 0;

    return str_copy_content(out, src);
}
