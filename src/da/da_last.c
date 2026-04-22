#include "da.h"
#include "memory.h"
#include "error.h"

fc_error_t __da_last
(def_da_header_t* da, void* out, uint32_t n_size)
{
    def_slice_t src = {0}, dst = {0};
    if(!da->items) { return fce_da_last_nullptr; }
    if(da->count == 0) { return fce_da_last_empty; }
    set_slice(&src, da->items + (da->count-1)*n_size, n_size);
    set_slice(&dst, (byte_t*)out, n_size);
    memcpy_ptr(&dst.base, &out);
    return fc_memcpy(dst, src);
}
