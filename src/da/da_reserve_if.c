#include "da_private.h"

fc_error_t __da_reserve_if
(const void* da, u32 amount, u32 el_size)
{
    /* Init variables */
    def_da_t* def = (void*)da;

    /* Validate user inputs -
     * el_size checked in __da_reserve and
     * amount can be zero in that case it wont change anything and success will returned
     */
    if(!def) { return fce_da_reserve_nullptr; }
    if(!amount) { return fce_success; }

    /* If it amount fits to memory return if not expand it */
    if(def->count + amount <= def->capacity) { return fce_success; }
    return __da_reserve(da, amount, el_size);
}
