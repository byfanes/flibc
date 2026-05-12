#include "stdio_private.h"

fc_error_t sprintf
(slice(u8) buf, usize_t* _Nullable wrote_count, slice(u8) fmt, ...)
{
    /* Init variables */
    va_list ap;
    fc_error_t res = fce_success;

    /* Start and end va and format string */
    va_start(ap, fmt);
    res = vsprintf(buf, wrote_count, fmt, ap);
    va_end(ap);

    return res;
}
