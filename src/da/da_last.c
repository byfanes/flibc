#include "da.h"
#include "memory.h"
#include "error.h"

fc_error_t __da_last
(def_da_header_t* da, void* out, uint32_t n_size)
{
    if(!da->items) {
        return fce_da_last_nullptr;
    }
    if(da->count == 0) {
        return fce_da_last_empty;
    }

    ptr_header_t src = { .base = (char*)da->items + (da->count-1)*n_size, .len = n_size, };
    ptr_header_t dst = { .base = out, .len = n_size, };
    return fc_memcpy(dst,src);
}
