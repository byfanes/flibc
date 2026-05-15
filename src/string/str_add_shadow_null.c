#include "string.h"

fc_error_t str_add_shadow_null
(str_t* str)
{
    return da_add_shadow_null_byte(str);
}
