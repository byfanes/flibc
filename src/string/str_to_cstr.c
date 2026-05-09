#include "string_private.h"

fc_error_t str_to_cstr
(str_t base, char** out)
{
    /* Init variables */
    fc_error_t res = fce_success;
    slice_t dst = {0}, src = {0};
    
    /* Validate user input */
    if(!out) { return fce_str_to_cstr_out_null; }

    /* If string is null return a null cstr */
    if(!base || !base->items) {
        return calloc(1, out);
    }        

    res = malloc(base->count + 1, out);
    if(res) { return res; }
    
    /* Set slices for copying */
    set_slice(&src, base->items, base->count);
    set_slice(&dst, (*out), base->count);

    /* Copy the data and set last byte to null */
    res = memcpy(dst, src);
    (*out)[base->count] = 0;

    if(res) { free(out); return res; }
    return fce_success;
}
