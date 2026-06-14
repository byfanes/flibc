#include "da_private.h"

error_t da_truncate
(void* da, usz len)
{
    /* Init variables */
    def_da_t* def = da;

    /* Validate user inputs */
    if(!def || !def->items) { return null_pointer; }

    /* Check and set if its in the range */
    if(len <= def->count) { def->count = len; }

    return success;
}
