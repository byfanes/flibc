#include "memory_private.h"
#include "error.h"

error_t __memswap_sl
(void* lhs, void* rhs, usz el_size)
{
    /* Init variables */
    sl_u8_t *lsl = lhs, *rsl = rhs;

    /* Validate user inputs - items checked in memswap_raw */
    if(!lsl || !rsl) { return null_pointer; }
    if(lsl->count != rsl->count) { return memswap_diffsize; }

    /* Swap memory and return */
    return memswap_raw(lsl->items, rsl->items, lsl->count * el_size);
}
