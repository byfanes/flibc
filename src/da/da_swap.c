#include "da.h"
#include "memory.h"
#include "error.h"

fc_error_t __da_swap
(def_da_header_t* da, uint32_t lhs, uint32_t rhs, uint32_t n_size)
{
    if(!da->items) {
        return fce_da_get_nullptr;
    }
    if(lhs >= da->count || rhs >= da->count) {
        return fce_da_get_outofbounds;
    }
    ptr_header_t lhs_src = { .base = (char*)da->items + lhs*n_size , .len = n_size, };
    ptr_header_t rhs_src = { .base = (char*)da->items + rhs*n_size , .len = n_size, };
    return fc_memswap(lhs_src,rhs_src);
}
