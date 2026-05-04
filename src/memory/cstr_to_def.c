#include "memory_private.h"

slice_t cstr_to_def
(const char* cstr)
{
    slice_t sl = {0};
    u32 i = 0;

    sl.base = (void*)cstr;
    if(cstr) { while(cstr[i++]){}; i--; }
    __set_slice_count(sl, i);

    return sl;
}
