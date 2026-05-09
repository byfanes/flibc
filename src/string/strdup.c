#include "string_private.h"

fc_error_t strdup
(str_t base, str_t* out)
{
    /* Init variables */
    fc_error_t res = fce_success;
    slice_t dst = {0}, src = {0};

    /* Validate user input */
    if(!out) { return fce_strdup_out_null; }
    if(!base) { return fce_strdup_base_null; }

    /* Reserve a memory */
    res = da_reserve(out, base->count);
    if(res) { return res; }

    /* Set slices for copying */
    set_slice(&src, base->items, base->count);
    set_slice(&dst, (*out)->items, base->count);

    *(u32*)(uintptr_t)&(*out)->count = base->count;

    /* Copy and return the result */
    return memcpy(dst, src);
}
