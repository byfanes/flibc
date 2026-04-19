#include "memory.h"
#include "error.h"

fc_error_t fc_memcpy
(def_slice_t dst, def_slice_t src)
{
    byte_t *pdst, *psrc;
    uint32_t i;
    if(!dst.base || !src.base) { return fce_mem_memcpy_nullptr; }
    if(src.count > dst.count) { return fce_mem_memcpy_smaller; }
    pdst = dst.base;
    psrc = src.base;
    for(i = 0; i < src.count; ++i) { *(pdst++) = *(psrc++); }
    return fce_success;
}
