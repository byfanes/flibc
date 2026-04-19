#include "memory.h"
#include "error.h"

fc_error_t fc_realloc
(uint32_t n, void* set)
{
    uint8_t *ptr, *newptr;
    uint32_t count;
    heap_header_t base;
    fc_error_t res;
    def_slice_t src, dst;
    if(!set) { return fce_mem_realloc_nullptr; }
    memcpy_ptr(&ptr, set);
    if(*ptr) {
        memcpy_sized(&base, ptr - sizeof(heap_header_t), sizeof(heap_header_t));
        count = base.alloced;
        if(count > n) { return fce_mem_realloc_shrink; }
    }
    if((res = fc_malloc(n, &newptr))) { return res; }
    conv_heap_to_ptr(ptr, &src);
    conv_heap_to_ptr(newptr, &dst);
    if((res = fc_memcpy(dst, src))) { return res; }
    if((res = fc_free(set))) { return res; }
    memcpy_ptr(set, &ptr);
    return fce_success;
}
