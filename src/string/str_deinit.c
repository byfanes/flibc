#include "string_private.h"

fc_error_t str_deinit
(str_t* out)
{
    /* This is a wrapper function */
    return da_deinit(out);
}
