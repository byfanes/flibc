#include "da_private.h"

error_t __da_unordered_remove
(void* da, usz el_size, usz idx)
{
    /* Init variables */
    def_da_t *def = da;
    error_t res = success;

    return ((void)(
        /* Check user inputs - def->count being zero checked in idx < def->count*/
        (res = (def && def->items) ? success : null_pointer) ||
        (res = (el_size) ? success : elsize_zero) ||
        (res = (idx < def->count) ? success : out_of_bounds) ||
        /* Move the end of data to current idx */
        (res = mem_move_raw(def->items + idx * el_size,
                            def->items + (def->count - 1) * el_size,
                            el_size)) ||
        (def->count--, success)
    ), res);
}
