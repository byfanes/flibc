#include "string_private.h"

fc_error_t str_utf8len
(str_t base, u32* out)
{
    slice_t sl = {0};
    
    if(!out) { return fce_str_utf8len_out_null; }
    if(!base) { *out = 0; return fce_success; }
    if(!base->items || !base->count) { *out = 0; return fce_success; }

    sl.base = (void*)base->items;
    __set_slice_count(sl, base->count);
    
    return sl_utf8len(sl, out);
}
