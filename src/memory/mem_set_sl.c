#include "memory_private.h"
#include "error.h"

error_t __mem_set_sl
(void* dst, usz el_size, u8 c)
{
    /* Init variable */
    sl_u8_t *dsl = dst;

    /* Validate user inputs - elsize can be given 0 -
     * items checked in memset_raw
     */
    if(!dsl) { return null_pointer;}
    if(!el_size) { return elsize_zero;}

    /* Set the memory */
    return mem_set_raw(dsl->items, c, el_size * dsl->count);
}
