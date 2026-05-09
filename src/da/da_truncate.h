#include "da_private.h"

fc_error_t da_truncate
(const void* da, u32 len)
{
    /* Init variables */
    def_da_t* def = da;

    /* Validate user inputs */
    if(!def) { return fce_da_truncate_nullptr; }

    /* Check and set if its in the range */
    if(len <= def->count) { def->count = len; }

    return fce_success;
}
