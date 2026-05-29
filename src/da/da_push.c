#include "da_private.h"

error_t __da_push
(void* da, usize_t el_size, void* item)
{
    /* Init variables */
    def_da_t* def = da;

    /* This is a wrapper function other checks will be done in da_insert function */
    if(!def) { return null_pointer; }
    return __da_insert(def, el_size, item, def->count);
}
