#include "memory.h"
#include "error.h"

fc_error_t fc_memmove
(ptr_header_t dst, ptr_header_t src)
{
    if(!dst.base || !src.base) { return fce_mem_memmove_nullptr; }
    if(src.len > dst.len) { return fce_mem_memmove_smaller; }
    char* pdst = dst.base;
    char* psrc = src.base;
    char buf[4096] = {0};
    char* tmp = {0};
    fc_error_t res = fce_success;
    if(src.len <= 4096) {
        tmp = buf;
    } else {
        if((res = fc_malloc(src.len,(void**)&tmp))) {
            return res;
        }
    }
    char* tmp2 = tmp;
    for(uint32_t i = 0; i < src.len; ++i) {
        *(tmp++) = *(psrc++);
    }
    for(uint32_t i = 0; i < src.len; ++i) {
        *(pdst++) = *(tmp2++);
    }
    if(src.len > 4096) {
        return fc_free((void**)&tmp);
    } else {
        return fce_success;
    }
}

