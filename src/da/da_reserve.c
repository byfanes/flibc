#include "da_private.h"

fc_error_t __da_reserve
(const void* da, u32 amount, u32 el_size)
{
    /* Init variables */
    def_da_t* def = (void*)da;

    /* Validate user inputs - n_size can not be 0 via sizeof but user implicitly call with it */
    if(!def) { return fce_da_reserve_nullptr; }
    if(!el_size) { return fce_da_reserve_zero_nsize; }
    if(!amount) { return fce_da_reserve_zero_amount; }

    /* Fetch and set new size */
    def->capacity += amount;

    /* Allocate new chunk of memory x*/
    return realloc(def->capacity * el_size, def->items);
}
