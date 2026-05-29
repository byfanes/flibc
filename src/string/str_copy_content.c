#include "string_private.h"

error_t __str_copy_content
(str_t* str, const void* ptr, usize_t amount)
{
    /* Init variables */
    sl_u8_t dst = {0}, src = {0};

    /* Fetch and set data */
    set_slice(&dst, &str->items[str->count], amount);
    set_slice(&src, ptr, amount);

    /* Move data and increase the count if its successful */
    return da_push_sl(str, &src);
}
