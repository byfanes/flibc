#include "da_private.h"

fc_error_t __da_swap
(const void* da, u32 lhs, u32 rhs, u32 el_size)
{
    /* Init variables */
    def_da_t* def = (void*)da;
    u32 i = 0; u8 c = 0;

    /* Validate user inputs - el_size can not be 0 via sizeof but user implicitly call with it */
    if(!def) { return fce_da_swap_nullptr; }
    if(!el_size) { return fce_da_swap_zero_nsize; }
    if(lhs >= def->count) { return fce_da_swap_lhs_out_of_bounds; }
    if(rhs >= def->count) { return fce_da_swap_rhs_out_of_bounds; }

    /* Swap items[lhs] with items[rhs] */
    for(; i < el_size; ++i) {
        c = def->items[i + rhs*el_size];
        def->items[i + rhs*el_size] = def->items[i + lhs*el_size];
        def->items[i + lhs*el_size] = c;
    }

    return fce_success;
}
