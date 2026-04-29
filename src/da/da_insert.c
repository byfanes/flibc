#include "da_private.h"

fc_error_t __da_insert
(void* da, void* in, uint32_t idx, uint32_t n_size)
{
    /* Init variables */
    fc_error_t res = fce_success;
    def_da_t *def = da;
    char *p_in = in;
    uint32_t count = 0, i = 0;
    slice_t src = {0}, dst = {0};

    /* Validate user inputs - n_size can not be 0 via sizeof but user implicitly call with it */
    if(!def) { return fce_da_insert_da_nullptr; }
    if(!in) { return fce_da_insert_in_nullptr; }
    if(!n_size) { return fce_da_insert_zero_nsize; }
    if(idx > def->count) { return fce_da_insert_out_of_bounds; }

    /* This acts like a grow function because header is already allocated */
    res = __da_reserve_if(&def, 1, n_size);
    def->count++;
    if(res) { return res; }

    /* Set bases for the moving */
    src.base = &def->items[idx * n_size];
    dst.base = &def->items[(idx + 1) *n_size];

    /* Set counts for the moving */
    count = (def->count - idx - 1) * n_size;
    __set_slice_count(src, count);
    __set_slice_count(dst, count);

    /* Shift the memory */
    res = memcpy(dst, src);
    if(res) { return res; }

    /* Add the new blob */
    for(;i < n_size; ++i) {
        def->items[idx*n_size + i] = p_in[i];
    }

    return fce_success;
}
