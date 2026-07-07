#include "da_private.h"

error_t __da_pop
(void* da, usz el_size, void* out, usz idx)
{
    /* Init variables */
    def_da_t *def = da;
    error_t res = success;

    return ((void)(
        /* Check user input */
        (res = (def && out && def->items) ? success : null_pointer) ||
        (res = (el_size) ? success : elsize_zero) ||
        (res = (idx < def->count) ? success : out_of_bounds) ||
        /* Copy the data to users' memory and remove it from the list */
        (res = mem_cpy_raw(out, def->items + idx * el_size, el_size)) ||
        (res = __da_remove(da, idx, el_size))
    ), res);
}
