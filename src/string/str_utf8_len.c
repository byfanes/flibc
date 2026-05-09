#include "string_private.h"

fc_error_t str_utf8len
(str_t base, u32* out)
{
    /* Init variables */
    slice_t sl = {0};

    /* Validate user input and early returns */
    if(!out) { return fce_str_utf8len_out_null; }
    if(!base) { *out = 0; return fce_success; }
    if(!base->items || !base->count) { *out = 0; return fce_success; }

    /* Set slice for length checking */
    set_slice(&sl, base->items, base->count);

    /* Use sl_utf8len function to calculate */
    return sl_utf8len(sl, out);
}
