#include "string_private.h"

bool __sl_is_utf8
(void* sl, usz el_size)
{
    /* Init variables */
    usz count = 0;
    sl_u8_t* ssl = sl;

    return (!ssl || !ssl->items || !ssl->count)
        && !(__sl_utf8_len(sl, el_size, &count));
}
