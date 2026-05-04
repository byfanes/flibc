#include "da_private.h"

fc_error_t __da_remove
(void* da, u32 idx, u32 n_size)
{
    /* Init variables */
    def_da_t *def = da;
    u32 count  = 0;
    slice_t src = {0}, dst = {0};

    /* Validate user inputs - n_size can not be 0 via sizeof but user implicitly call with it */
    if(!def) { return fce_da_remove_nullptr; }
    if(!n_size) { return fce_da_remove_zero_nsize; }
    if(idx >= def->count) { return fce_da_remove_out_of_bounds; }

    /* Set bases for the moving */
    src.base = &def->items[(idx + 1) * n_size];
    dst.base = &def->items[idx * n_size];
    count = (def->count - idx - 1) * n_size;

    /* Set counts for the moving */
    __set_slice_count(src, count);
    __set_slice_count(dst, count);

    def->count--;

    /* Shift the memory and return the result */
    return memcpy(dst, src);
}
