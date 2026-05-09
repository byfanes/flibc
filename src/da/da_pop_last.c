#include "da_private.h"

fc_error_t __da_pop_last
(const void* da, void* out, u32 el_size)
{
    /* Init variables */
    def_da_t *def = (void*)da;

    /* Validate user inputs - el_size can not be 0 via sizeof
     * but user implicitly call with it checked in __da_pop function
     */
    if(!def) { return fce_da_pop_nullptr; }
    if(!def->count) { return fce_da_pop_out_of_bounds; }

    return __da_pop(da, out, def->count - 1, el_size);
}
