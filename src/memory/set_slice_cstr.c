#include "memory_private.h"

error_t set_slice_cstr
(const void* sl, const char* str)
{
    return set_slice(sl, str, strlen(str));
}
