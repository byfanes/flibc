#include "da_private.h"

fc_error_t __da_grow
(void* da, usize_t amount, usize_t el_size)
{
    /* Init variables */
    def_da_t* def = da;
    allocator_t* alloc = 0;

    /* Validate user inputs
     * n_size can not be 0 via sizeof but user implicitly call with it
     * if amount is zero do nothing.
     */
    if(!def) { return fce_null_pointer; }
    if(!el_size) { return fce_elsize_zero; }
    if(!amount) { return fce_success; }

    /* Fetch and set new size */
    def->capacity += amount;

    /* Get allocator */
    if(allocator_get_from_ptr(def->items, &alloc)) { return fce_invalid_pointer; }

    /* Get new chun of memory */
    return realloc(alloc, def->capacity * el_size, &def->items);
}
