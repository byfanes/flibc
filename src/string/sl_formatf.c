#include "string_private.h"

error_t sl_formatf
(sl_u8_t buf, usz* _Nullable wrote_count, const char* fmt, ...)
{
    /* Init variables */
    va_list ap;
    error_t res = success;

    /* Start and end va and format string */
    va_start(ap, fmt);
    res = sl_vformatf_sl(buf, wrote_count, cstr_to_u8sl(fmt), ap);
    va_end(ap);

    return res;
}
