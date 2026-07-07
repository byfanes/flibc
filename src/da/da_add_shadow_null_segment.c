#include "da_private.h"

error_t __da_add_shadow_null_segment
(void* da, usz el_size)
{
    /* Init variables */
    def_da_t* def = da;
    error_t res = success;

    return ((void)(
        /* Check input */
        (res = (def && def->items) ? success : null_pointer) ||
        /* If count and capacity is same its alread pointing to zeroed place
         * if not we jump to that place and put zero
         */
        (res = (def->count == def->capacity) ? success
             : mem_zeroed_len((def->items + def->count * el_size), sizeof(usz)))
    ), res);
}
