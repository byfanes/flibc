#include "da.h"
#include "memory.h"
#include "error.h"

fc_error_t __da_pop_first
(def_da_header_t* da, void* out, uint32_t n_size)
{
    fc_error_t res = fce_success;
    def_slice_t src = {0}, dst = {0}, out_src = {0}, out_dst = {0};
    if(!da->items) { return fce_da_pop_first_nullptr; }
    if(da->count == 0) { return fce_da_pop_first_empty; }

    set_slice(&src, da->items + n_size, n_size*(da->count-1));
    set_slice(&dst, da->items, src.count);
    set_slice(&out_src, da->items, n_size);
    set_slice(&out_dst, out, n_size);

    da->count--;
    if(out) { if((res = fc_memcpy(out_dst, out_src))) { return res; } }
    return fc_memmove(dst, src);
}
