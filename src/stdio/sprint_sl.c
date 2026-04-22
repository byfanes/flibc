#include "stdio.h"

fc_error_t sprintf_sl
(def_slice_t buf, def_slice_t fmt, ...)
{
    va_list va;
    fc_error_t res = fce_success;
    va_start(va, fmt);
    res = vsprintf_sl(buf, fmt, va);
    va_end(va);
    return res;
}
