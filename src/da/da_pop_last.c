#include "da_private.h"

fc_error_t __da_pop_last
(void* da, void* out, uint32_t n_size)
{
    /* Init variables */
    def_da_t *def = da;

    /* Validate user inputs - n_size can not be 0 via sizeof but user implicitly call with it */
    if(!def) { return fce_da_pop_nullptr; }
    if(!n_size) { return fce_da_pop_zero_nsize; }
    if(!def->count) { return fce_da_pop_out_of_bounds; }

    return __da_pop(da, out, def->count - 1, n_size);
}
