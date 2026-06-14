#include "memory_private.h"
#include "error.h"

error_t __memcmp
(void* lhs, void* rhs, usz el_size, bool* out)
{
    /* Init variables */
    sl_u8_t *lsl = lhs, *rsl = rhs;
    usz i = 0;

    /* Validate user inputs */
    if(!lsl || !rsl || !out || !lsl->items || !rsl->items) { return null_pointer; }
    if(lsl->count != rsl->count) { *out = false; return success; }
    if(!el_size) { return elsize_zero; }

    /* Iterate over bases and compare them */
    for (; i < lsl->count * el_size; ++i) {
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
