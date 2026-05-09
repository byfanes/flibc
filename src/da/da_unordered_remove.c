#include "da_private.h"

fc_error_t __da_unordered_remove
(const void* da, u32 idx, u32 el_size)
{
    /* Init variables */
    def_da_t *def = (void*)da;
    u32 i = 0;

    /* Validate user inputs - n_size can not be 0 via sizeof but user implicitly call with it */
    if(!def) { return fce_da_unordered_remove_nullptr; }
    if(!el_size) { return fce_da_unordered_remove_zero_nsize; }
    if(idx >= def->count) { return fce_da_unordered_remove_out_of_bounds; }

    /* Set items[idx] items[last] */
    for(i = 0; i < el_size; ++i) {
        def->items[i + idx*el_size] = def->items[i + (def->count - 1)*el_size];
    }

    /* Remove last element */
    def->count--;
    return fce_success;
}
