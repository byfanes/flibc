#include "da_private.h"

error_t da_clear
(void* da)
{
    /* Init variables */
    def_da_t* def = da;

    /* Check input */
    if(!def) { return null_pointer; }

    /* Set count to zero without modify items */
    def->count = 0;
    return success;
}
