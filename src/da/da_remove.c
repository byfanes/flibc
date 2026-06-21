#include "da_private.h"

error_t __da_remove
(void* da, usz el_size, usz idx)
{
    /* Init variables */
    def_da_t *def = da;
    usz count  = 0;
    sl_u8_t src = {0}, dst = {0};

    /* Validate user inputs - el_size can not be 0 via sizeof but user implicitly call with it */
    if(!def || !def->items) { return null_pointer; }
    if(!el_size) { return elsize_zero; }
    if(idx >= def->count) { return out_of_bounds; }

    /* Set slices for the moving. Arguments are valid in here so no need to check */
    slice_set(&src, &def->items[(idx + 1) * el_size], count);
    slice_set(&dst, &def->items[idx * el_size], count);
    count = (def->count - idx - 1) * el_size;

    /* Decrease count */
    def->count--;

    /* Shift the memory and return the result */
    return mem_move(&dst, &src);
}
