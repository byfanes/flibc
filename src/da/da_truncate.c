#include "da_private.h"

error_t da_truncate
(void* da, usz len)
{
    /* Init variables */
    def_da_t* def = da;

    /* Check user pointers are valid then trucate to that given size */
    return (!def || !def->items) ? null_pointer
       : ((def->count = (len <= def->count)
           ? len : def->count), success);
}
