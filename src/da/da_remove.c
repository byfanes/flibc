#include "da_private.h"

fc_error_t __da_remove
(const void* da, u32 idx, u32 el_size)
{
    /* Init variables */
    def_da_t *def = (void*)da;
    u32 count  = 0;
    slice_t src = {0}, dst = {0};

    /* Validate user inputs - el_size can not be 0 via sizeof but user implicitly call with it */
    if(!def) { return fce_da_remove_nullptr; }
    if(!el_size) { return fce_da_remove_zero_nsize; }
    if(idx >= def->count) { return fce_da_remove_out_of_bounds; }

    /* Set slices for the moving */
    set_slice(&src, &def->items[(idx + 1) * el_size], count);
    set_slice(&dst, &def->items[idx * el_size], count);
    count = (def->count - idx - 1) * el_size;

    def->count--;

    /* Shift the memory and return the result */
    return memcpy(dst, src);
}
