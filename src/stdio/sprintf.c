#include "stdio_private.h"

fc_error_t sprintf
(slice_t buf, u32* _Nullable wrote_count, slice_t fmt, ...)
{
    va_list ap;
    fc_error_t res = fce_success;
    va_start(ap, fmt);
    res = vsprintf(buf, wrote_count, fmt, ap);
    va_end(ap);
    return res;
}
