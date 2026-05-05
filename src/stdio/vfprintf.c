#include "stdio_private.h"

fc_error_t vfprintf
(file_t* file, slice_t fmt, va_list ap)
{
    u32 count = 0;
    fc_error_t res = fce_success;
    u8 buf[4096];
    va_list c_ap;
    slice_t buf_sl = {0};

    va_copy(c_ap, ap);
    res = formatf(buf_sl, fmt, c_ap, &count);
    if(res) { return res; }

    __set_slice_count(buf_sl, count);
    if(count > sizeof(buf)) {
        res = malloc(count, &buf_sl.base);
        if(res) { return res; }
    } else {
        buf_sl.base = buf;
    }

    res = formatf(buf_sl, fmt, ap, &count);
    if(res) { return res; }

    fwrite(file, buf_sl);

    if(count > sizeof(buf)) {
        return free(&buf_sl.base);
    }

    return fce_success;
}
