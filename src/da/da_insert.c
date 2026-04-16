#include "da.h"
#include "memory.h"
#include "error.h"

fc_error_t __da_insert
(def_da_header_t* da, uint32_t idx, uint32_t n_size)
{
    fc_error_t res = fce_success;
    if(!da->items) {
        if ((res = __da_reserve(da,n_size,FLIBC_DA_INIT))) { return res; }
    }
    if(idx > da->count) {
        return fce_da_insert_outofbounds;
    }
    if ((res = __da_reserve(da,n_size,1))) { return res; }
    def_slice_t src = { .base = da->items + n_size*idx, .len = (da->count-idx)*n_size, };
    def_slice_t dst = { .base = da->items + n_size*(idx+1), .len = src.len, };
    return fc_memmove(dst,src);
}
