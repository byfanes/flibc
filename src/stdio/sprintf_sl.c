#include "stdio_private.h"

error_t sprintf_sl
(sl_u8_t buf, usz* _Nullable wrote_count, sl_u8_t fmt, ...)
{
    /* Init variables */
    va_list ap;
    error_t res = success;

    /* Start and end va and format string */
    va_start(ap, fmt);
    res = vsprintf_sl(buf, wrote_count, fmt, ap);
    va_end(ap);

    return res;
}
