#include "memory_private.h"
#include "error.h"

error_t __mem_cmp_sl_min
(void* lhs, void* rhs, usz el_size, bool* out)
{
    /* Init variables */
    sl_u8_t *lsl = lhs, *rsl = rhs;
    usz count = 0;

    return
        (!lsl || !rsl) ? null_pointer :
        (!el_size) ? elsize_zero :
        (count = (lsl->count > rsl->count) ? rsl->count : lsl->count,
            mem_cmp_raw(lsl->items, rsl->items, count * el_size, out));
}
