#include "stdio.h"

extern fc_error_t __printf_format(def_slice_t buf, def_slice_t fmt, va_list va);
extern fc_error_t __printf_size(def_slice_t fmt, uint32_t* out, va_list va);

fc_error_t vsprintf_sl
(def_slice_t buf,def_slice_t fmt, va_list va)
{
    va_list va_c;
    uint32_t needed = 0;
    fc_error_t res = fce_success;
    va_copy(va_c, va);
    if((res = __printf_size(fmt, &needed, va_c))) { return res; }
    if(needed > buf.count) { return fce_printf_small_buffer; }
    return __printf_format(buf, fmt, va);
}
