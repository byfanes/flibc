#include "io_private.h"

error_t io_vprintf
(file_t* file, const char* fmt, va_list ap)
{
    sl_u8_t fmt_sl = {0};
    error_t res = success;

    return ((void)(
        (res = slice_set_cstr(&fmt_sl, fmt)) ||
        (res = io_vprintf_sl(file, fmt_sl, ap))
    ), res);
}
