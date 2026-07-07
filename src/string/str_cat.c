#include "string_private.h"

error_t str_cat
(str_t* base, str_t* extend)
{
    /* Init variables */
    error_t res = success;

    return ((void)(
        /* Validate user input */
        (res = (base && base->items) ? success : null_pointer) ||
        /* If its a null slice/pointer skip it */
        (!extend || !extend->items || !extend->count) ||
        /* Grow string memory if needed */
        (res = str_grow_if(base, extend->count)) ||
        /* Copy the elements to string */
        (res = __str_copy_content(base, extend->items, extend->count))
    ), res);
}
