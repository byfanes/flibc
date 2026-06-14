#include "string_private.h"

bool __is_utf8_sl
(void* sl, usz el_size)
{
    /* Init variables */
    usz count = 0;
    sl_u8_t* ssl = sl;

    /* Validate user input */
    if(!ssl || !ssl->items || !ssl->count) { return true; }

    /* Call sl_utf8len it checks for valid strings */
    if(__sl_utf8len(sl, el_size, &count)) { return false; }

    /* Return */
    return true;
}
