#include "string_private.h"

error_t str_cat_cstr
(str_t* base, const char* cstr)
{
    /* Init variables */
    sl_u8_t sl = {0};

    /* This is a wrapper function and strlen can be given null which will return 0 */
    return (slice_set(&sl, cstr, cstr_len(cstr)), str_cat_sl(base, &sl));
}
