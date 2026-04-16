#include "memory.h"
#include "error.h"

fc_error_t fc_memmove
(def_slice_t dst, def_slice_t src)
{
    if(!dst.base || !src.base) { return fce_mem_memmove_nullptr; }
    if(src.len > dst.len) { return fce_mem_memmove_smaller; }
    byte_t* pdst = dst.base;
    byte_t* psrc = src.base;
    byte_t buf[4096] = {0};
    byte_t* tmp = {0};
    fc_error_t res = fce_success;
    if(src.len <= 4096) {
        tmp = buf;
    } else {
        if((res = fc_malloc(src.len,(void**)&tmp))) {
            return res;
        }
    }
    byte_t* tmp2 = tmp;
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

