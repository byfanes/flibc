#include "string_private.h"

fc_error_t str_grow_if
(str_t* str, usize_t amount)
{
    /* This is a wrapper function */
    return da_grow_if(str, amount);
}
