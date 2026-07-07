#include "string_private.h"

error_t sl_formatf
(sl_u8_t buf, usz* _Nullable wrote_count, const char* fmt, ...)
{
    /* Init variables */
    va_list ap;
    error_t res = success;
    sl_u8_t fmt_sl = {0};

    return ((void)(
        /* Start and end va and format string */
        (va_start(ap, fmt), (void)(
            (res = slice_set_cstr(&fmt_sl, fmt) ) ||
            (res = sl_vformatf_sl(buf, wrote_count, fmt_sl, ap))
        ), va_end(ap), res)
    ), res);
}
