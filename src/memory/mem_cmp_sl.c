#include "memory_private.h"
#include "error.h"

error_t __mem_cmp_sl
(const void *lhs, const void *rhs, usz el_size, bool* out)
{
    /* Init variables */
    const sl_u8_t *lsl = lhs, *rsl = rhs;

    return
        (!lsl || !rsl || !out) ? null_pointer :
        (!el_size) ? elsize_zero :
        (lsl->count != rsl->count) ? (error_t)(*out = false, success) :
        mem_cmp_raw(lsl->items, rsl->items, lsl->count * el_size, out);
}
