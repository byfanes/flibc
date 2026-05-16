#include "da_private.h"

error_t __da_pop_last
(void* da, void* out, usize_t el_size)
{
    /* Init variables */
    def_da_t *def = da;

    /* Validate user inputs - el_size can not be 0 via sizeof
     * but user implicitly call with it checked in __da_pop function
     */
    if(def->count == 0) { return out_of_bounds; }

    return __da_pop(da, out, def->count - 1, el_size);
}
