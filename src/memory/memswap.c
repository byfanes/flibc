#include "memory_private.h"
#include "error.h"

fc_error_t __memswap
(void* lhs, void* rhs, usize_t el_size)
{
    /* Init variables */
    slice(u8) *lsl = lhs, *rsl = rhs;
    u8 c = 0, i = 0;

    /* Validate user inputs */
    if(!lsl || !rsl || !lsl->base || !rsl->base) { return fce_null_pointer; }
    if(lsl->count != rsl->count) { return fce_memswap_diffsize; }

    /* Iter 'i' times on the slices' bases and swap them */
    for(; i < lsl->count * el_size; ++i) {
        c = lsl->base[i];
        lsl->base[i] = rsl->base[i];
        rsl->base[i] = c;
    }

    return fce_success;
}
