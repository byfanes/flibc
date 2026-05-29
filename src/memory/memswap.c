#include "memory_private.h"
#include "error.h"

error_t __memswap
(void* lhs, void* rhs, usize_t el_size)
{
    /* Init variables */
    sl_u8_t *lsl = lhs, *rsl = rhs;
    u8 c = 0, i = 0;

    /* Validate user inputs */
    if(!lsl || !rsl || !lsl->items || !rsl->items) { return null_pointer; }
    if(lsl->count != rsl->count) { return memswap_diffsize; }

    /* Iter 'i' times on the slices' itemss and swap them */
    for(; i < lsl->count * el_size; ++i) {
        c = lsl->items[i];
        lsl->items[i] = rsl->items[i];
        rsl->items[i] = c;
    }

    return success;
}
