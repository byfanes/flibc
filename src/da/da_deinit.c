#include "da_private.h"

error_t da_deinit
(void* da)
{
    /* Init variables */
    def_da_t *def = da;
    error_t res = success;

    return ((void)(
        /* Check input values */
        (res = (def) ? success : null_pointer) ||
        /* Free the memory */
        (res = mem_free(&def->items)) ||
        /* If freeing is succesful erase earlier data otherwise restore it */
        (res = mem_zeroed(def))
    ), res);
}
