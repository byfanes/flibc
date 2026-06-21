#include "io_private.h"

error_t io_printf_sl
(file_t* file, sl_u8_t fmt, ...)
{
    /* Init variables */
    va_list ap;
    error_t res = success;

    /* Start and end va and format string */
    va_start(ap, fmt);
    res = io_vprintf_sl(file, fmt, ap);
    va_end(ap);

    return res;
}
