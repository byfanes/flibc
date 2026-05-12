#include "da_private.h"

fc_error_t __da_init
(allocator_t* alloc, void* da, usize_t amount, usize_t el_size)
{
    /* Init variables */
    fc_error_t res = fce_success;
    def_da_t *def = da;

    /* Check inputs */
    if(!el_size || !alloc || !def) { return fce_null_pointer; }

    /* Allocate new memory for items */
    if((res = malloc(alloc, amount * el_size, &def->items)))
    { return res; }

    /* Set stats for the da */
    def->count = 0;
    def->capacity = amount;

    /* Return */
    return fce_success;
}
