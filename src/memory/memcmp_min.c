#include "memory_private.h"
#include "error.h"

error_t __memcmp_min
(void* lhs, void* rhs, usize_t el_size, bool* out)
{
    /* Init variables */
    sl_u8_t *lsl = lhs, *rsl = rhs;
    usize_t count = 0, i = 0;

    /* Validate user inputs */
    if(!lsl || !rsl || !out || !lsl->items || !rsl->items) { return null_pointer; }
    if(!el_size) { return elsize_zero; }

    /* Set min size */
    count = (lsl->count > rsl->count) ? rsl->count : lsl->count;

    /* Iterate over itemss and compare them */
    for (; i < count * el_size; ++i) {
        if(lsl->items[i] != rsl->items[i]) {
            /* Does not match */
            *out = false;
            return success;
        }
    }

    /* Does match */
    *out = true;
    return success;
}
