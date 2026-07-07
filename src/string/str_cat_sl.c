#include "string_private.h"

error_t __str_cat_sl
(str_t* base, void* raw_sl, usz el_size)
{
    /* Init variables */
    error_t res = success;
    sl_u8_t* ssl = raw_sl;

    return ((void)(
        /* Validate user input */
        (res = (el_size) ? success : elsize_zero) ||
        (res = (base && base->items) ? success : null_pointer) ||
        /* Early return if its a null slice/pointer */
        (!ssl || !ssl->items || !ssl->count) ||
        /* Check for utf8 */
        (res = (!__sl_is_utf8(raw_sl, el_size)) ? success : invalid_utf8 ) ||
        /* Allocate new memory if needed  */
        (res = str_grow_if(base, ssl->count)) ||
        /* Copy the data */
        (res = __str_copy_content(base, ssl->items, el_size * ssl->count))
    ), res);
}
