#include "da_private.h"

error_t __da_unordered_remove
(void* da, usize_t idx, usize_t el_size)
{
    /* Init variables */
    def_da_t *def = da;
    usize_t i = 0;

    /* Validate user inputs - n_size can not be 0 via sizeof but user implicitly call with it */
    if(!def || !def->items) { return null_pointer; }
    if(!el_size) { return elsize_zero; }
    if(idx >= def->count) { return out_of_bounds; }

    /* Set items[idx] items[last] */
    for(i = 0; i < el_size; ++i) {
        def->items[i + idx*el_size] = def->items[i + (def->count - 1)*el_size];
    }

    /* Remove last element */
    def->count--;
    return success;
}
