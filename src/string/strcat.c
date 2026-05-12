#include "string_private.h"

fc_error_t strcat
(str_t* base, str_t* extend)
{
    /* Init variables */
    fc_error_t res = fce_success;
    slice(u8) src = {0};

    /* Validate user input */
    if(!base || !base->items) { return fce_null_pointer; }
    if(!extend || !extend->items || !extend->count) { return fce_success; }

    /* Grow string memory if needed */
    if((res = str_grow_if(base, extend->count))) { return res; }

    /* Set slices for copying */
    set_slice(&src, extend->items, extend->count);
    return __str_copy_content(base, src);
}
