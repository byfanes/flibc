#include "da_private.h"

error_t __da_insert
(void* da, usz el_size, void* in, usz idx)
{
    /* Init variables */
    error_t res = success;
    def_da_t *def = da;
    u8 *p_in = in;
    usz count = 0, i = 0;
    sl_u8_t src = {0}, dst = {0};

    /* Validate user inputs - el_size can not be 0 via sizeof but user implicitly call with it */
    if(!def || !p_in) { return null_pointer; }
    if(!el_size) { return elsize_zero; }
    if(idx > def->count) { return out_of_bounds; }

    /* Check if it fits allocate otherwise  */
    if((res = __da_grow_if(def, el_size, 1))) { return res; }
    def->count++;

    /* Set slices for the moving */
    count = (def->count - idx - 1) * el_size;
    set_slice(&src, &def->items[idx * el_size], count);
    set_slice(&dst, &def->items[(idx + 1) *el_size], count);

    /* Shift the memory */
    if((res = memmove(&dst, &src))) { return res; }

    /* Add the new blob */
    for(;i < el_size; ++i) {
        def->items[idx*el_size + i] = p_in[i];
    }

    return success;
}
