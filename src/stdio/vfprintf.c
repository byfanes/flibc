#include "stdio_private.h"

error_t vfprintf
(file_t* file, const char* fmt, va_list ap)
{
    return vfprintf_sl(file, cstr_to_u8sl(fmt), ap);
}
