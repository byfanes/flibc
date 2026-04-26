#include "memory_private.h"

def_slice_t cstr_to_def
(const char* cstr)
{
    def_slice_t sl = {0};
    uint32_t i = 0;

    sl.base = (void*)cstr;
    if(cstr) { while(cstr[i++]){}; i--; }
    __set_slice_count(sl, i);

    return sl;
}
