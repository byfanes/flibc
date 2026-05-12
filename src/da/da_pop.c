#include "da_private.h"

fc_error_t __da_pop
(void* da, void* out, usize_t idx, usize_t el_size)
{
    /* Init variables */
    def_da_t *def = da;
    usize_t i = 0;
    u8 *p_out = out;

    /* Validate user inputs - el_size can not be 0 via sizeof but user implicitly call with it */
    if(!def || !p_out || !def->items) { return fce_null_pointer; }
    if(!el_size) { return fce_elsize_zero; }
    if(idx >= def->count) { return fce_out_of_bounds; }

    /* Copy last itme to out */
    for(;i < el_size; ++i) {
        p_out[i] = def->items[idx * el_size + i];
    }

    /* Remove the last element from the array */
    return __da_remove(da, idx, el_size);
}
