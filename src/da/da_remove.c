#include "da.h"
#include "memory.h"
#include "error.h"

fc_error_t __da_remove
(def_da_header_t* da, uint32_t idx, uint32_t n_size)
{
    fc_error_t res = fce_success;
    def_slice_t src = {0}, dst = {0};
    if(!da->items) { return fce_da_remove_nullptr; }
    if(idx >= da->count) { return fce_da_remove_index_outofbounds; }
    set_slice(&src, da->items + n_size*(idx+1), (da->count-idx-1)*n_size);
    set_slice(&dst, da->items + n_size*idx, src.count);
    da->count--;
    res = fc_memmove(dst, src);
    return res;
}
