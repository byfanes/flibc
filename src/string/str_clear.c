#include "string_private.h"

error_t str_clear
(str_t* str)
{
    return da_clear(str);
}
