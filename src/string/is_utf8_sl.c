#include "string_private.h"

bool is_utf8_sl
(slice_t sl)
{
    /* Init variables */
    u32 count = 0;
    
    /* Validate user input */
    if(!sl.base || !sl.count) { return true; }

    /* Call sl_utf8len it checks for valid strings */
    if(sl_utf8len(sl, &count)) { return false; }

    /* Return */
    return true;
}
