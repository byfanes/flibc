#include "string_private.h"

error_t sl_vformatf
(sl_u8_t buf, usz* _Nullable wrote_count, const char* fmt, va_list ap)
{
    return sl_vformatf_sl(buf, wrote_count, cstr_to_u8sl(fmt), ap);
}
