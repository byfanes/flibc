#include "memory.h"
#include "error.h"

fc_error_t memswap
(slice_t lhs, slice_t rhs)
{
    /* Init variables */
    u8 c = 0;
    u32 i = 0;
    
    /* Validate user inputs */
    if(!lhs.base || !rhs.base) { return fce_mem_memswap_nullptr; }
    if(lhs.count != rhs.count) { return fce_mem_memswap_diffsize; }

    /* Iter 'i' times on the slices' bases and swap them */
    for(; i < lhs.count; ++i) {
        c = *lhs.base;
        lhs.base[i] = *rhs.base;
        rhs.base[i] = c;
    }
    
    return fce_success;
}
