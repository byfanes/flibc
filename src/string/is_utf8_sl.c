#include "string_private.h"

fc_error_t is_utf8_sl
(slice_t sl, bool* out)
{
    /* Init variables */
    u32 count = 0;
    
    /* Validate user input */
    if(!out) { return fce_is_utf8_sl_out_null; }
    if(!sl.base || !sl.count) { *out = true; return fce_success; }

    /* Call sl_utf8len it checks for valid strings */
    *out = true;
    if(sl_utf8len(sl, &count)) { *out = false; }

    /* Return */
    return fce_success;
}
