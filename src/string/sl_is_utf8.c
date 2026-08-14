#include "string_private.h"

bool __sl_is_utf8
(const void *sl, usz el_size)
{
    /* Init variables */
    usz count = 0;
    const sl_u8_t *ssl = sl;

    return (!ssl || !ssl->items) && !(__sl_utf8_len(sl, el_size, &count));
}
