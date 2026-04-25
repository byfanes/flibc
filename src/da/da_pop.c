#include "da_private.h"

fc_error_t __da_pop
(void* da, void* out, uint32_t idx, uint32_t n_size)
{
    /* Init variables */
    def_da_t *def = da;
    uint32_t i = 0;
    byte_t* p_out = out;

    /* Validate user inputs - n_size can not be 0 via sizeof but user implicitly call with it */
    if(!def) { return fce_da_pop_nullptr; }
    if(!n_size) { return fce_da_pop_zero_nsize; }
    if(idx >= def->count) { return fce_da_pop_out_of_bounds; }

    /* Copy last itme to out */
    for(;i < n_size; ++i) {
        p_out[i] = def->items[idx * n_size + i];
    }

    /* Remove the last element from the array */
    return __da_remove(da, idx, n_size);
}
