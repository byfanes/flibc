#include "da_private.h"

fc_error_t __da_remove
(void* da, usize_t idx, usize_t el_size)
{
    /* Init variables */
    def_da_t *def = da;
    usize_t count  = 0;
    slice(u8) src = {0}, dst = {0};

    /* Validate user inputs - el_size can not be 0 via sizeof but user implicitly call with it */
    if(!def || !def->items) { return fce_null_pointer; }
    if(!el_size) { return fce_elsize_zero; }
    if(idx >= def->count) { return fce_out_of_bounds; }

    /* Set slices for the moving. Arguments are valid in here so no need to check */
    set_slice(&src, &def->items[(idx + 1) * el_size], count);
    set_slice(&dst, &def->items[idx * el_size], count);
    count = (def->count - idx - 1) * el_size;

    /* Decrease count */
    def->count--;

    /* Shift the memory and return the result */
    return memcpy(&dst, &src);
}
