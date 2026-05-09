#include "string_private.h"

fc_error_t strcat
(str_t* base, str_t extend)
{
    /* Init variables */
    fc_error_t res = fce_success;
    slice_t src = {0};

    /* Validate user input */
    if(!base) { return fce_strcat_base_null; }
    if(!extend.items || !extend.count) { return fce_success; }
    if(!base->items) { return fce_strcat_base_null; }

    /* Grow string memory if needed */
    res = str_reserve_if(base, extend.count);
    if(res) { return res; }

    /* Set slices for copying */
    set_slice(&src, extend.items, extend.count);
    return str_copy_content(base, src);
}
