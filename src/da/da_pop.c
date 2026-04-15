#include "da.h"
#include "memory.h"
#include "error.h"

fc_error_t __da_pop
(def_da_header_t* da, void* out, uint32_t n_size)
{
    if(!da->items) {
        return fce_da_pop_nullptr;
    }
    if(da->count == 0) {
        return fce_da_pop_empty;
    }

    if(!out) {
        da->count--;
        return fce_success;
    }
    
    ptr_header_t src = { .base = (char*)da->items + n_size*(da->count-1),
                         .len = n_size, };
    ptr_header_t dst = { .base = out, .len = n_size, };
    da->count--;
    return fc_memcpy(dst,src);
}
