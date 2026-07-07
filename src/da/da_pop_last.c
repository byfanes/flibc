#include "da_private.h"

error_t __da_pop_last
(void* da, usz el_size, void* out)
{
    /* Init variables */
    def_da_t *def = da;

    /* Check def because we use it before going into function */
    return (!def) ? null_pointer
        : (!def->count) ? out_of_bounds
        : __da_pop(da, el_size, out, def->count - 1);
}
