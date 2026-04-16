#include "memory.h"
#include "error.h"

fc_error_t fc_realloc
(uint32_t n,void** set)
{
    if(!set) { return fce_mem_realloc_nullptr; }
    uint32_t count = 0;
    if(*set) {
        heap_header_t* base = ((heap_header_t*)*set - 1);
        count = base->alloced;
        if(count > n) { return fce_mem_realloc_shrink; }
    }
    void* ptr = 0;
    fc_error_t res = fce_success;
    if((res = fc_malloc(n,&ptr))) { return res; }
    def_slice_t src = conv_heap_to_ptr(*set);
    def_slice_t dst = conv_heap_to_ptr(ptr);
    if((res = fc_memcpy(dst,src))) { return res; }
    if((res = fc_free(set))) { return res; }
    *set = ptr;
    return fce_success;
}
