#include "memory_private.h"
#include "error.h"

error_t __memcmp
(void* lhs, void* rhs, usize_t el_size, bool* res)
{
    /* Init variables */
    slice(u8) *lsl = lhs, *rsl = rhs;
    usize_t i = 0;

    /* Validate user inputs */
    if(!lsl || !rsl || !res || !lsl->base || !rsl->base) { return null_pointer; }
    if(lsl->count != rsl->count) { *res = false; return success; }
    if(!el_size) { return elsize_zero; }

    /* Iterate over bases and compare them */
    for (; i < lsl->count * el_size; ++i) {
        if(lsl->base[i] != rsl->base[i]) {
            /* Does not match */
            *res = false;
            return success;
        }
    }

    /* Does match */
    *res = true;
    return success;
}
