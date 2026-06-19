#include "memory_private.h"
#include "error.h"

error_t __memcmp_sl
(void* lhs, void* rhs, usz el_size, bool* out)
{
    /* Init variables */
    sl_u8_t *lsl = lhs, *rsl = rhs;

    /* Validate user inputs - items checked in memcmp_raw */
    if(!lsl || !rsl || !out) { return null_pointer; }
    if(lsl->count != rsl->count) { *out = false; return success; }
    if(!el_size) { return elsize_zero; }

    /* Iterate over bases and compare them */
    return memcmp_raw(lsl->items, rsl->items, lsl->count * el_size, out);
}
