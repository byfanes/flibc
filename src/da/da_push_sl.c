#include "da_private.h"

error_t __da_push_sl
(void* da, usz el_size, void* sl)
{
    /* Init variables */
    error_t res = success;
    def_da_t *def = da;
    sl_u8_t *ssl = sl;

    return ((void)(
        /* Check user input if count is zero early return */
        (res = (def && ssl) ? success : null_pointer) ||
        (!ssl->count) ||
        (res = (ssl->items) ? success : null_pointer) ||
        (res = (el_size) ? success : elsize_zero) ||
        /* Check if it fits other wise allocate new memory and update the count */
        (res = __da_grow_if(da, el_size, ssl->count)) ||
        (def->count += ssl->count, success) ||
        /* Add the new blob */
        (res = mem_move_raw(def->items + el_size * (def->count - ssl->count),
                            ssl->items, ssl->count * el_size))
    ), res);
}
