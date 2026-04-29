#include "da_private.h"

fc_error_t __da_unordered_remove
(void* da, void* out, uint32_t idx, uint32_t n_size)
{
    /* Init variables */
    def_da_t *def = da;
    char *p_out = out;
    uint32_t i = 0;

    /* Validate user inputs - n_size can not be 0 via sizeof but user implicitly call with it */
    if(!out && !def) { return fce_da_unordered_remove_nullptr; }
    if(!n_size) { return fce_da_unordered_remove_zero_nsize; }
    if(idx >= def->count) { return fce_da_unordered_remove_out_of_bounds; }

    /* Set out to items[idx] */
    for(; i < n_size; ++i) {
        p_out[i] = def->items[i + idx*n_size];
    }

    /* Set items[idx] items[last] */
    for(i = 0; i < n_size; ++i) {
        p_out[i] = def->items[i + (def->count - 1)*n_size];
    }

    /* Remove last element */
    def->count--;
    return fce_success;
}
