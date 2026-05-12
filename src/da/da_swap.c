#include "da_private.h"

fc_error_t __da_swap
(void* da, usize_t lhs, usize_t rhs, usize_t el_size)
{
    /* Init variables */
    def_da_t* def = da;
    usize_t i = 0;
    u8 c = 0;

    /* Validate user inputs - el_size can not be 0 via sizeof but user implicitly call with it */
    if(!def || !def->items) { return fce_null_pointer; }
    if(!el_size) { return fce_elsize_zero; }
    if(lhs >= def->count) { return fce_out_of_bounds; }
    if(rhs >= def->count) { return fce_out_of_bounds; }

    /* Swap items[lhs] with items[rhs] */
    for(; i < el_size; ++i) {
        c = def->items[i + rhs*el_size];
        def->items[i + rhs*el_size] = def->items[i + lhs*el_size];
        def->items[i + lhs*el_size] = c;
    }

    return fce_success;
}
