#include "memory.h"
#include "error.h"

fc_error_t fc_memcpy
(ptr_header_t dst, ptr_header_t src)
{
    if(!dst.base || !src.base) { return fce_mem_memcpy_nullptr; }
    if(src.len > dst.len) { return fce_mem_memcpy_smaller; }
    char* pdst = dst.base;
    char* psrc = src.base;
    for(uint32_t i = 0; i < src.len; ++i) {
        *(pdst++) = *(psrc++);
    }
    return fce_success;
}
