#include "string_private.h"

error_t str_deinit
(str_t* out)
{
    /* This is a wrapper function */
    return da_deinit(out);
}
