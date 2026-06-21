#include "io_private.h"

error_t io_vprintf
(file_t* file, const char* fmt, va_list ap)
{
    return io_vprintf_sl(file, cstr_to_u8sl(fmt), ap);
}
