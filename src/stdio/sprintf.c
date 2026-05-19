#include "stdio_private.h"

error_t sprintf
(slice(u8) buf, usize_t* _Nullable wrote_count, const char* fmt, ...)
{
    /* Init variables */
    va_list ap;
    error_t res = success;

    /* Start and end va and format string */
    va_start(ap, fmt);
    res = vsprintf_sl(buf, wrote_count, cstr_to_u8sl(fmt), ap);
    va_end(ap);

    return res;
}
