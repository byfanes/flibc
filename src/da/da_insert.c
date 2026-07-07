#include "da_private.h"

error_t __da_insert
(void* da, usz el_size, void* in, usz idx)
{
    /* Init variables */
    error_t res = success;
    def_da_t *def = da;

    return ((void)(
        /* Validate user input */
        (res = (def && in) ? success : null_pointer) ||
        (res = (el_size) ? success : elsize_zero) ||
        (res = (idx <= def->count) ? success : out_of_bounds) ||
        /* Check if the new element fits if not allocate more and update the count*/
        (res = __da_grow_if(def, el_size, 1)) ||
        (def->count++, success) ||
        /* Shift the current data block */
        (res = mem_move_raw(def->items + (idx + 1) * el_size,
                            def->items + idx * el_size,
                            (def->count - idx - 1) * el_size)) ||
        /* Insert the new data block */
        (res = mem_cpy_raw(&def->items[idx*el_size], in, el_size))
    ), res);
}
