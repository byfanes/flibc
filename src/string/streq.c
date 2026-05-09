#include "string_private.h"

fc_error_t streq
(str_t lhs, str_t rhs, bool* out)
{
    u32 i = 0;
    
    if(!out) { return fce_streq_out_null; }
    if(!lhs.items && !rhs.items) { goto success; }
    if(lhs.items && !rhs.items) { goto fail; }
    if(!lhs.items && rhs.items) { goto fail; }
    if(lhs.count != rhs.count) { goto fail; }

    for(;i < lhs.count; ++i) {
        if(lhs.items[i] != rhs.items[i]) { goto fail; }
    }
success:
    *out = true;
    return fce_success;
fail:
    *out = false;
    return fce_success;
}
