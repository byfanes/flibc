#include "string_private.h"

error_t strcat
(str_t* base, str_t* extend)
{
    /* Init variables */
    error_t res = success;
    slice(u8) src = {0};

    /* Validate user input */
    if(!base || !base->items) { return null_pointer; }
    if(!extend || !extend->items || !extend->count) { return success; }

    /* Grow string memory if needed */
    if((res = str_grow_if(base, extend->count))) { return res; }

    /* Set slices for copying */
    set_slice(&src, extend->items, extend->count);
    return __str_copy_content(base, src);
}
