#include "string_private.h"

fc_error_t strcat_sl
(str_t base, slice_t sl)
{
    /* Init variables */
    bool is_utf8 = false;
    fc_error_t res = fce_success;
    slice_t dst = {0};

    /* Validate user input */
    if(!base || !base->items) { return fce_strcat_sl_base_null; }
    if(!sl.base || !sl.count) { return fce_success; }
    
    /* Check for utf8 */
    res = is_utf8_sl(sl, &is_utf8);
    if(res) { return res; }
    if(!is_utf8) { return fce_strcat_sl_not_utf8; }

    /* This acts like a grow function because header is already allocated */
    res = __da_reserve_if(&base, sl.count, sizeof(*base->items));
    if(res) { return res; }
    
    /* Set slices for memcpy */
    dst.base = (void*)&base->items[base->count];
    __set_slice_count(dst, sl.count);

    /* Copy the data */
    res = memcpy(dst, sl);
    if(res) { return res; }

    /* Incrase the count if its successful */
    *(u32*)(uintptr_t)&base->count += sl.count;
    return fce_success;
}
