#include "io_private.h"

error_t io_printf
(file_t* file, const char* fmt, ...)
{
    /* Init variables */
    va_list ap;
    error_t res = success;

    /* Start and end va and format string */
    va_start(ap, fmt);
    res = io_vprintf_sl(file, cstr_to_u8sl(fmt), ap);
    va_end(ap);

    return res;
}
