#include "da_private.h"

error_t __da_grow
(void* da, usz el_size, usz amount)
{
    /* Init variables */
    def_da_t* def = da;
    allocator_t* alloc = 0;

    /* Validate user inputs
     * n_size can not be 0 via sizeof but user implicitly call with it
     * if amount is zero do nothing.
     */
    if(!def) { return null_pointer; }
    if(!el_size) { return elsize_zero; }
    if(!amount) { return success; }

    /* Fetch and set new size */
    def->capacity += amount;

    /* Get allocator */
    if(allocator_get_from_ptr(def->items, &alloc)) { return invalid_pointer; }

    /* Get new chun of memory */
    return realloc(alloc, def->capacity * el_size, &def->items);
}
