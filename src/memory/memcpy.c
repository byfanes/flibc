#include "memory.h"
#include "error.h"

fc_error_t fc_memcpy
(def_slice_t dst, def_slice_t src)
{
    if(!dst.base || !src.base) { return fce_mem_memcpy_nullptr; }
    if(src.count > dst.count) { return fce_mem_memcpy_smaller; }
    byte_t* pdst = dst.base;
    byte_t* psrc = src.base;
    for(uint32_t i = 0; i < src.count; ++i) {
        *(pdst++) = *(psrc++);
    }
    return fce_success;
}
