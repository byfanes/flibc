#include "memory.h"
#include "error.h"

fc_error_t fc_realloc
(uint32_t n,void* set)
{
    uint8_t* ptr = 0;
    if(!set) { return fce_mem_realloc_nullptr; }
    memcpy_sized(&ptr,set,sizeof(void*));
    uint32_t count = 0;
    if(*ptr) {
        heap_header_t base = {0};
        memcpy_sized(&base,ptr - sizeof(heap_header_t),sizeof(heap_header_t));
        count = base.alloced;
        if(count > n) { return fce_mem_realloc_shrink; }
    }
    fc_error_t res = fce_success;
    void* newptr = 0;
    if((res = fc_malloc(n,&newptr))) { return res; }
    def_slice_t src = conv_heap_to_ptr(ptr);
    def_slice_t dst = conv_heap_to_ptr(newptr);
    if((res = fc_memcpy(dst,src))) { return res; }
    if((res = fc_free(set))) { return res; }
    memcpy_sized(set,&ptr,sizeof(void*));
    return fce_success;
}
