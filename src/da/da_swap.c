#include "da_private.h"

error_t __da_swap
(void* da, usz el_size, usz lhs, usz rhs)
{
    /* Init variables */
    def_da_t* def = da;
    error_t res = success;

    return ((void)(
        /* Check user inputs */
        (res = (def && def->items) ? success : null_pointer) ||
        (res = (el_size) ? success : elsize_zero) ||
        (res = (lhs >= def->count) ? success : out_of_bounds) ||
        (res = (rhs >= def->count) ? success : out_of_bounds) ||
        /* Swap the memory - having same addres is safe it checks for that */
        (res = mem_swap_raw(def->items + rhs*el_size,
                            def->items + lhs*el_size,
                            el_size))
    ), res);
}
