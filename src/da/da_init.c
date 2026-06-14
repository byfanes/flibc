#include "da_private.h"

error_t __da_init
(allocator_t* alloc, void* da, usz el_size, usz amount)
{
    /* Init variables */
    error_t res = success;
    def_da_t *def = da;

    /* Check inputs */
    if(!el_size) { return elsize_zero; }
    if(!alloc || !def) { return null_pointer; }

    /* Allocate new memory for items */
    if((res = malloc(alloc, amount * el_size, &def->items)))
    { return res; }

    /* Set stats for the da */
    def->count = 0;
    def->capacity = amount;

    /* Return */
    return success;
}
