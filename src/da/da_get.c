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
    ptr_header_t out_src = { .base = out, .len = n_size, };
    ptr_header_t idx_src = { .base = (char*)da->items + idx*n_size , .len = n_size, };
    return fc_memcpy(out_src,idx_src);
}
