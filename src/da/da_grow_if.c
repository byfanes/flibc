#include "da_private.h"

error_t __da_grow_if
(void* da, usz el_size, usz amount)
{
    /* Init variables */
    def_da_t* def = da;
    error_t res = success;

    return ((void)(
        /* Check input variables */
        (res = (def) ? success : null_pointer) ||
        /* Check the range if it fits its true so skip the pipeline */
        (amount <= def->capacity - def->count) ||
        /* Grow the dynamic array - el_size zero handled here */
        (res = __da_grow(da, el_size, amount))
    ), res);
}
