#include "da_private.h"

fc_error_t __da_insert
(void* da, void* in, usize_t idx, usize_t el_size)
{
    /* Init variables */
    fc_error_t res = fce_success;
    def_da_t *def = da;
    u8 *p_in = in;
    usize_t count = 0, i = 0;
    slice(u8) src = {0}, dst = {0};

    /* Validate user inputs - el_size can not be 0 via sizeof but user implicitly call with it */
    if(!def || !p_in) { return fce_null_pointer; }
    if(!el_size) { return fce_elsize_zero; }
    if(idx > def->count) { return fce_out_of_bounds; }

    /* Check if it fits allocate otherwise  */
    if((res = __da_grow_if(def, 1, el_size))) { return res; }
    def->count++;

    /* Set slices for the moving */
    count = (def->count - idx - 1) * el_size;
    set_slice(&src, &def->items[idx * el_size], count);
    set_slice(&dst, &def->items[(idx + 1) *el_size], count);

    /* Shift the memory */
    if((res = memcpy(&dst, &src))) { return res; }

    /* Add the new blob */
    for(;i < el_size; ++i) {
        def->items[idx*el_size + i] = p_in[i];
    }

    return fce_success;
}
