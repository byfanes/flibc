#include "string.h"

error_t str_add_shadow_null
(str_t* str)
{
    return da_add_shadow_null_segment(str);
}
