#include "da.h"
#include "memory.h"
#include "error.h"

fc_error_t __da_get
(def_da_header_t* da, uint32_t idx, uint32_t n_size, void* out)
{
    if(!da->items) {
        return fce_da_get_nullptr;
    }
    if(idx >= da->count) {
        return fce_da_get_outofbounds;
    }
    def_slice_t out_src = { .base = (byte_t*)out, .count = n_size, };
    def_slice_t idx_src = { .base = da->items + idx*n_size , .count = n_size, };
    return fc_memcpy(out_src,idx_src);
}
