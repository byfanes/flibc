#include "da.h"
#include "memory.h"
#include "error.h"

fc_error_t __da_unordered_remove
(def_da_header_t* da, uint32_t idx, uint32_t n_size, void* out)
{
    fc_error_t res;
    def_slice_t idx_src, last_src, out_src;

    if(!da->items) { return fce_da_unordered_remove_nullptr; }
    if(idx >= da->count) { return fce_da_unordered_remove_outofbounds; }

    set_slice(&idx_src, da->items + idx*n_size, n_size);
    set_slice(&last_src, da->items + (da->count-1)*n_size, n_size);
    if(out) {
        set_slice(&out_src, nullptr, n_size);
        memcpy_sized(&out_src, &out, sizeof(void*));
        if((res = fc_memcpy(out_src, idx_src))) { return res; }
    }
    if((res = fc_memcpy(idx_src, last_src))) { return res; }
    da->count--;
    return res;
}
