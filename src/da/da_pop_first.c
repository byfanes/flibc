#include "da.h"
#include "memory.h"
#include "error.h"

fc_error_t __da_pop_first
(def_da_header_t* da, void* out, uint32_t n_size)
{
    if(!da->items) {
        return fce_da_pop_first_nullptr;
    }
    if(da->count == 0) {
        return fce_da_pop_first_empty;
    }
    fc_error_t res = fce_success;

    def_slice_t src = { .base = da->items + n_size, .count = n_size*(da->count-1), };
    def_slice_t dst = { .base = da->items, .count = src.count, };

    def_slice_t out_src = { .base = da->items, .count = n_size, };
    def_slice_t out_dst = { .base = (byte_t*)out, .count = n_size, };
    da->count--;
    if(out) {
        if((res = fc_memcpy(out_dst,out_src))) { return res; }
    }
    return fc_memmove(dst,src);
}
