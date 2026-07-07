#include "string_private.h"

error_t sl_vformatf
(sl_u8_t buf, usz* _Nullable wrote_count, const char* fmt, va_list ap)
{
    sl_u8_t fmt_sl = {0};
    error_t res = success;

    return ((void)(
        (res = slice_set_cstr(&fmt_sl, fmt)) ||
        (res = sl_vformatf_sl(buf, wrote_count, fmt_sl, ap))
    ),res);
}
