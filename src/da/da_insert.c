#include "da.h"
#include "memory.h"
#include "error.h"

fc_error_t __da_insert
(def_da_header_t* da, uint32_t idx, uint32_t n_size)
{
    fc_error_t res = fce_success;
    def_slice_t src = {0}, dst = {0};
    if(!da->items) { if ((res = __da_reserve(da, n_size, FLIBC_DA_INIT))) { return res; } }
    if(idx > da->count) { return fce_da_insert_outofbounds; }
    if ((res = __da_reserve(da, n_size, 1))) { return res; }
    set_slice(&src, da->items + n_size*idx, (da->count-idx)*n_size);
    set_slice(&dst, da->items + n_size*(idx+1), src.count);
    return fc_memmove(dst, src);
}
