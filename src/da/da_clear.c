#include "da_private.h"

error_t da_clear
(void* da)
{
    /* Init variables */
    def_da_t* def = da;

    /* Check input if its valid set the count to zero */
    return (def) ? (def->count = 0, success) : null_pointer;
}
