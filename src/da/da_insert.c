#include "da_private.h"

fc_error_t __da_insert
(const void* da, void* in, u32 idx, u32 el_size)
{
    /* Init variables */
    fc_error_t res = fce_success;
    def_da_t *def = (void*)da;
    u8 *p_in = in;
    u32 count = 0, i = 0;
    slice_t src = {0}, dst = {0};

    /* Validate user inputs - el_size can not be 0 via sizeof but user implicitly call with it */
    if(!def) { return fce_da_insert_da_nullptr; }
    if(!in) { return fce_da_insert_in_nullptr; }
    if(!el_size) { return fce_da_insert_zero_nsize; }
    if(idx > def->count) { return fce_da_insert_out_of_bounds; }

    /* This acts like a grow function because header is already allocated */
    res = __da_reserve_if(da, 1, el_size);
    def->count++;
    if(res) { return res; }

    /* Set slices for the moving */
    count = (def->count - idx - 1) * el_size;
    set_slice(&src, &def->items[idx * el_size], count);
    set_slice(&dst, &def->items[(idx + 1) *el_size], count);

    /* Shift the memory */
    res = memcpy(dst, src);
    if(res) { return res; }

    /* Add the new blob */
    for(;i < el_size; ++i) {
        def->items[idx*el_size + i] = p_in[i];
    }

    return fce_success;
}
