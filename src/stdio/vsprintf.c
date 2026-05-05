#include "stdio_private.h"

fc_error_t vsprintf
(slice_t buf, u32* _Nullable wrote_count, slice_t fmt, va_list ap)
{
    u32 count = 0;
    fc_error_t res = fce_success;
    va_list c_ap;
    slice_t buf_sl = {0};
    
    if(wrote_count) { *wrote_count = 0; }
    
    va_copy(c_ap, ap);
    res = formatf(buf_sl, fmt, c_ap, &count);
    if(res) { return res; }

    if(buf.count < count) { return fce_sprintf_small_buffer; }
    
    res = formatf(buf, fmt, ap, &count);
    if(res) { return res; }

    if(wrote_count) { *wrote_count = count; }
    return fce_success;
}
