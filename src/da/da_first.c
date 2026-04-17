#include "da.h"
#include "memory.h"
#include "error.h"

fc_error_t __da_first
(def_da_header_t* da, void* out, uint32_t n_size)
{
    if(!da->items) {
        return fce_da_first_nullptr;
    }
    if(da->count == 0) {
        return fce_da_first_empty;
    }

    def_slice_t src = { .base = da->items, .count = n_size, };
    def_slice_t dst = { .base = nullptr, .count = n_size, };
    memcpy_sized(&dst.base,&out,sizeof(void*));
    return fc_memcpy(dst,src);
}
