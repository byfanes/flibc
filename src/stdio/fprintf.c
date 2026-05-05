#include "stdio_private.h"

fc_error_t fprintf
(file_t* file, slice_t fmt, ...)
{
    va_list ap;
    fc_error_t res = fce_success;
    va_start(ap, fmt);
    res = vfprintf(file, fmt, ap);
    va_end(ap);
    return res;
}
