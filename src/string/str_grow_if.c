#include "string_private.h"

error_t str_grow_if
(str_t* str, usz amount)
{
    /* This is a wrapper function */
    return da_grow_if(str, amount);
}
