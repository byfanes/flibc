#include "da.h"
#include "memory.h"
#include "error.h"

fc_error_t __da_pop
(def_da_header_t* da, void* out, uint32_t n_size)
{
    def_slice_t src = {0}, dst = {0};
    
    if(!da->items) { return fce_da_pop_nullptr; }
    if(da->count == 0) { return fce_da_pop_empty; }
    if(!out) { da->count--; return fce_success;  }
    
    set_slice(&src, da->items + n_size*(da->count-1), n_size);
    set_slice(&dst, nullptr, n_size);
    memcpy_ptr(&dst.base, &out);
    da->count--;
    return fc_memcpy(dst, src);
}
