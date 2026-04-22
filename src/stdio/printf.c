#include "stdio.h"

fc_error_t printf
(const char* fmt, ...)
{
    va_list va;
    fc_error_t res = fce_success;
    def_slice_t sl_fmt;
    va_start(va, fmt);
    sl_fmt = fmt_from_cstr(fmt);
    res = vprintf_sl(sl_fmt, va);
    va_end(va);
    return res;
}
