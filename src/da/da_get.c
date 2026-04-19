#include "da.h"
#include "memory.h"
#include "error.h"

fc_error_t __da_get
(def_da_header_t* da, uint32_t idx, uint32_t n_size, void* out)
{
    def_slice_t out_src, idx_src;
    if(!da->items) { return fce_da_get_nullptr; }
    if(idx >= da->count) { return fce_da_get_outofbounds; }
    set_slice(&out_src, nullptr, n_size);
    memcpy_ptr(&out_src.base, &out);
    set_slice(&idx_src, da->items + idx*n_size, n_size);
    return fc_memcpy(out_src, idx_src);
}
