#include "da.h"
#include "memory.h"
#include "error.h"

fc_error_t __da_swap
(def_da_header_t* da, uint32_t lhs, uint32_t rhs, uint32_t n_size)
{
    def_slice_t lhs_src, rhs_src;
    if(!da->items) { return fce_da_get_nullptr;  }
    if(lhs >= da->count || rhs >= da->count) { return fce_da_get_outofbounds; }
    set_slice(&lhs_src, da->items + lhs*n_size, n_size);
    set_slice(&rhs_src, da->items + rhs*n_size, n_size);
    return fc_memswap(lhs_src, rhs_src);
}
