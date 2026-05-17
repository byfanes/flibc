#include "string_private.h"

error_t __str_copy_content
(str_t* str, slice(u8) src)
{
    /* Init variables */
    slice(u8) dst = {0};

    /* Fetch and set data */
    set_slice(&dst, &str->items[str->count], src.count);

    /* Move data and increase the count if its successful */
    return da_push_sl(str, &src);
}
