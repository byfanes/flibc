#include "string_private.h"

error_t __str_copy_content
(str_t* str, const void* ptr, usz amount)
{
    /* Init variables */
    sl_u8_t dst = {0}, src = {0};
    error_t res = success;

    return ((void)(
        /* Fetch and set data */
        (res = slice_set(&dst, &str->items[str->count], amount)) ||
        (res = slice_set(&src, ptr, amount)) ||
        /* Move data and increase the count if its successful */
        (res = da_push_sl(str, &src))
    ), res);
}
