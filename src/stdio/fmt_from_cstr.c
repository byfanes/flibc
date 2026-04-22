#include "stdio.h"
#include "memory.h"

def_slice_t fmt_from_cstr
(const char* str)
{
    uint32_t i;
    def_slice_t ret = {0};
    i = 0;
    while(str[i++]);
    set_slice(&ret, (byte_t*)str, i - 1);
    return ret;
}
