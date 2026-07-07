#include "memory_private.h"

error_t slice_set_cstr
(void* sl, const char* str)
{
    return slice_set(sl, str, cstr_len(str));
}
