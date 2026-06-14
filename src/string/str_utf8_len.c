#include "string_private.h"

error_t str_utf8len
(str_t* base, usz* out)
{
    /* Init variables */
    sl_u8_t sl = {0};

    /* Validate user input and early returns */
    if(!out || !base) { return null_pointer; }
    if(!base->items || !base->count) { *out = 0; return success; }

    /* Set slice for length checking */
    set_slice(&sl, base->items, base->count);

    /* Use sl_utf8len function to calculate */
    return sl_utf8len(&sl, out);
}
