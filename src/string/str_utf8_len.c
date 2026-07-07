#include "string_private.h"

error_t str_utf8_len
(str_t* base, usz* out)
{
    /* Init variables */
    sl_u8_t sl = {0};

    return
        /* Validate user input and early returns */
        (!out || !base) ? null_pointer :
        (!base->items || !base->count) ? (*out = 0, (error_t)success) :
        /* Set slice for length checking - Use sl_utf8len function to calculate*/
        (slice_set(&sl, base->items, base->count), sl_utf8_len(&sl, out));
}
