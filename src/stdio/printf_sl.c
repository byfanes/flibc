#include "stdio.h"

fc_error_t printf_sl
(def_slice_t fmt, ...)
{
    va_list va;
    fc_error_t res = fce_success;
    va_start(va, fmt);
    res = vprintf_sl(fmt, va);
    va_end(va);
    return res;
}
