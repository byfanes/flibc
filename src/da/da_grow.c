#include "da_private.h"

error_t __da_grow
(void* da, usz el_size, usz amount)
{
    /* Init variables */
    def_da_t* def = da;
    allocator_t* alloc = 0;
    error_t res = success;

    return ((void)(
        /* Validate user input if amount is zero early return from the pipeline */
        (res = (def) ? success : null_pointer) ||
        (res = (el_size) ? success : elsize_zero) ||
        /* Early return if amount is zero */
        (!amount) ||
        /* Get the allocator back if def->items is zero it will give an error */
        (res = allocator_get_from_ptr(def->items, &alloc)) ||
        /* Get new chunk of memory if its valid update the count */
        (res = mem_realloc(alloc, &def->items, (def->capacity + amount) * el_size)) ||
        (def->capacity += amount, success)
    ), res);
}
