#include "da_private.h"

fc_error_t __da_reserve_if
(void* p_da, u32 amount, u32 n_size)
{
    /* Init variables */
    def_da_t* da = 0;

    /* Validate user inputs -
     * n_size checked in __da_reserve and
     * amount can be zero in that case it wont change anything and success will returned
     */
    if(!p_da) { return fce_da_reserve_nullptr; }
    if(!amount) { return fce_success; }

    da = *(void**)p_da;

    /* If it amount fits to memory return if not expand it */
    if(da && da->count + amount <= da->capacity) { return fce_success; }
    return __da_reserve(p_da, amount, n_size);
    return fce_success;
}
