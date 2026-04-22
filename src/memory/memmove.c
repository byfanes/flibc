#include "memory.h"
#include "error.h"

fc_error_t fc_memmove
(def_slice_t dst, def_slice_t src)
{
    byte_t *tmp = 0, *tmp2 = 0, buf[FLIBC_STACK_THRESHOLD] = {0};
    fc_error_t res = fce_success;
    uint32_t i = 0;
    if(!dst.base || !src.base) { return fce_mem_memmove_nullptr; }
    if(src.count > dst.count) { return fce_mem_memmove_smaller; }
    tmp = 0;
    if(src.count <= FLIBC_STACK_THRESHOLD) {
        tmp = buf;
    } else {
        if((res = fc_malloc(src.count,&tmp))) { return res; }
    }
    tmp2 = tmp;
    for(i = 0; i < src.count; ++i) { *(tmp++)  = *(src.base++); }
    for(i = 0; i < src.count; ++i) { *(dst.base++) = *(tmp2++); }
    if(src.count > FLIBC_STACK_THRESHOLD) { return fc_free(&tmp); }
    return fce_success;
}

