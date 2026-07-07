#include "memory_private.h"
#include "error.h"

error_t __mem_swap_sl
(void* lhs, void* rhs, usz el_size)
{
    /* Init variables */
    sl_u8_t *lsl = lhs, *rsl = rhs;

    return
        (!lsl || !rsl) ? null_pointer :
        (lsl->count != rsl->count) ? memswap_diffsize :
        mem_swap_raw(lsl->items, rsl->items, lsl->count * el_size);
}
