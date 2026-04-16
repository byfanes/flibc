#include "memory.h"
#include "error.h"

fc_error_t fc_memcpy
(def_slice_t dst, def_slice_t src)
{
    if(!dst.base || !src.base) { return fce_mem_memcpy_nullptr; }
    if(src.len > dst.len) { return fce_mem_memcpy_smaller; }
    byte_t* pdst = dst.base;
    byte_t* psrc = src.base;
    for(uint32_t i = 0; i < src.len; ++i) {
        *(pdst++) = *(psrc++);
    }
    return fce_success;
}
