#include "stdio_private.h"

fc_error_t fprintf
(file_t* file, slice(u8) fmt, ...)
{
    /* Init variables */
    va_list ap;
    fc_error_t res = fce_success;

    /* Start and end va and format string */
    va_start(ap, fmt);
    res = vfprintf(file, fmt, ap);
    va_end(ap);

    return res;
}
