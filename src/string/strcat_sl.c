#include "string_private.h"

fc_error_t strcat_sl
(str_t* base, slice_t sl)
{
    /* Init variables */
    bool is_utf8 = false;
    fc_error_t res = fce_success;

    /* Validate user input */
    if(!base || !base->items) { return fce_strcat_sl_base_null; }
    if(!sl.base || !sl.count) { return fce_success; }
    
    /* Check for utf8 */
    res = is_utf8_sl(sl, &is_utf8);
    if(res) { return res; }
    if(!is_utf8) { return fce_strcat_sl_not_utf8; }

    /* This acts like a grow function because header is already allocated */
    res = str_reserve_if(base, sl.count);
    if(res) { return res; }


    /* Copy the data */
    return str_copy_content(base, sl);
}
