#include "stdio.h"

fc_error_t fprintf_sl
(file_t* file, def_slice_t fmt, ...)
{
    va_list va;
    fc_error_t res = fce_success;
    va_start(va, fmt);
    res = vfprintf_sl(file, fmt, va);
    va_end(va);
    return res;
}
