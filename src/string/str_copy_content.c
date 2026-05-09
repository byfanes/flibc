#include "string_private.h"

fc_error_t str_copy_content
(str_t* str, slice_t src)
{
    /* Init variables */
    fc_error_t res = fce_success;
    slice_t dst = {0};
    struct str_s* s = 0;

    /* Fetch and set data */
    s = (void*)str;
    set_slice(&dst, &str->items[str->count], src.count);

    /* Move data and increase the count if its successful */
    res = memcpy(dst, src);
    if(!res) { s->count += src.count; }
    
    return res;
}
