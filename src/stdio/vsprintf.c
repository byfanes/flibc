#include "stdio_private.h"

error_t vsprintf
(sl_u8_t buf, usz* _Nullable wrote_count, const char* fmt, va_list ap)
{
    return vsprintf_sl(buf, wrote_count, cstr_to_u8sl(fmt), ap);
}
