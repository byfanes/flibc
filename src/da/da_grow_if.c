#include "da_private.h"

error_t __da_grow_if
(void* da, elsize_t el_size, count_t amount)
{
    /* Init variables */
    def_da_t* def = da;

    /* Validate user inputs -
     * el_size checked in __da_reserve and
     * amount can be zero in that case it wont change anything and success will returned
     */
    if(!def) { return null_pointer; }
    if(!amount) { return success; }

    /* If it amount fits to memory return if not expand it */
    if(def->count + amount <= def->capacity) { return success; }
    return __da_grow(da, el_size, amount);
}
