#include "da.h"
#include "memory.h"
#include "error.h"

fc_error_t __da_unordered_remove
(def_da_header_t* da, uint32_t idx, uint32_t n_size, void* out)
{
    fc_error_t res = fce_success;
    if(!da->items) {
        return fce_da_unordered_remove_nullptr;
    }
    if(idx >= da->count) {
        return fce_da_unordered_remove_outofbounds;
    }
    def_slice_t idx_src = { .base = da->items + idx*n_size , .len = n_size, };
    def_slice_t last_src = { .base = da->items + (da->count-1)*n_size , .len = n_size, };
    if(out) {
        def_slice_t out_src = { .base = out, .len = n_size, };
        if((res = fc_memcpy(out_src,idx_src))) { return res; }
    }
    if((res = fc_memcpy(idx_src,last_src))) { return res; }
    da->count--;
    return res;
}
