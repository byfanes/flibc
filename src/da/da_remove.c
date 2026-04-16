#include "da.h"
#include "memory.h"
#include "error.h"

fc_error_t __da_remove
(def_da_header_t* da, uint32_t idx, uint32_t n_size)
{
    if(!da->items) {
        return fce_da_remove_nullptr;
    }
    if(idx >= da->count) {
        return fce_da_remove_index_outofbounds;
    }
    def_slice_t src = { .base = da->items + n_size*(idx+1), .len = (da->count-idx-1)*n_size, };
    def_slice_t dst = { .base = da->items + n_size*idx,.len = src.len, };
    da->count--;
    return fc_memmove(dst,src);
}
