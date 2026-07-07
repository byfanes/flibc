#include "da_private.h"

error_t __da_remove
(void* da, usz el_size, usz idx)
{
    /* Init variables */
    def_da_t *def = da;
    error_t res = success;

    return ((void)(
        /* Check user inputs */
        (res = (def && def->items) ? success : null_pointer) ||
        (res = (el_size) ? success : elsize_zero) ||
        (res = (idx < def->count) ? success : out_of_bounds) ||
        /* Shift the data to left*/
        (res = mem_move_raw(def->items + idx * el_size,
                            def->items + (idx + 1) * el_size,
                            (def->count - idx - 1) * el_size)) ||
        (def->count--, success)
    ), res);
}
