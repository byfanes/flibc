#include "da_private.h"

error_t __da_push_sl
(void* da, usz el_size, void* sl)
{
    /* Init variables */
    error_t res = success;
    def_da_t *def = da;
    sl_u8_t *ssl = sl, dsl = {0}, nsl = {0};

    /* Validate user inputs - el_size can not be 0 via sizeof but user implicitly call with it */
    if(!def || !ssl || !ssl->items) { return null_pointer; }
    /* __da_grow_if can do an early return without checking el_size so check it */
    if(!el_size) { return elsize_zero; }

    /* Check if it fits allocate otherwise  */
    if((res = __da_grow_if(da, el_size, ssl->count))) { return res; }
    def->count += ssl->count;

    /* Set slices for the moving. Arguments are valid in here so no need to check */
    set_slice(&dsl, &def->items[el_size * (def->count - ssl->count)], ssl->count * el_size);
    set_slice(&nsl, ssl->items, ssl->count * el_size);

    return memmove(&dsl, &nsl);
}
