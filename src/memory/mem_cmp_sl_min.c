#include "memory_private.h"
#include "error.h"

error_t __mem_cmp_sl_min
(void* lhs, void* rhs, usz el_size, bool* out)
{
    /* Init variables */
    sl_u8_t *lsl = lhs, *rsl = rhs;
    usz count = 0;

    /* Validate user inputs - items and out checked in memcmp_raw */
    if(!lsl || !rsl) { return null_pointer; }
    if(!el_size) { return elsize_zero; }

    /* Set min size */
    count = (lsl->count > rsl->count) ? rsl->count : lsl->count;
    return mem_cmp_raw(lsl->items, rsl->items, count * el_size, out);
}
