#include "da_private.h"

error_t __da_init
(allocator_t* alloc, void* da, usz el_size, usz amount)
{
    /* Init variables */
    error_t res = success;
    def_da_t *def = da;

    return ((void)(
        /* Validate user input */
        (res = (el_size) ? success : elsize_zero) ||
        (res = (alloc && def) ? success : null_pointer) ||
        /* Get the new memory and set the count and capacity if it succeeds */
        (res = mem_alloc(alloc, &def->items, amount * el_size)) ||
        (def->count = 0, def->capacity = amount)
    ), res);
}
