#include "io_private.h"

error_t io_printf
(file_t* file, const char* fmt, ...)
{
    /* Init variables */
    va_list ap;
    error_t res = success;
    sl_u8_t fmt_sl = {0};

    return (
        /* Start va_list block and pass to io_vprintf_sl to handle rest */
        (va_start(ap, fmt), (void)(
            (res = slice_set_cstr(&fmt_sl, fmt)) ||
            (res = io_vprintf_sl(file, fmt_sl, ap))
        ), va_end(ap))
    , res);
}
