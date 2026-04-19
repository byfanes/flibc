#include "da.h"
#include "memory.h"
#include "error.h"

fc_error_t __da_first
(def_da_header_t* da, void* out, uint32_t n_size)
{
    def_slice_t src, dst;
    if(!da->items) { return fce_da_first_nullptr; }
    if(da->count == 0) { return fce_da_first_empty; }
    set_slice(&src, da->items, n_size);
    set_slice(&dst, nullptr, n_size);
    memcpy_ptr(&dst.base, &out);
    return fc_memcpy(dst, src);
}
