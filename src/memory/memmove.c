#include "memory.h"
#include "error.h"

fc_error_t memmove
(slice_t dst, slice_t src)
{
    /* Init variables */
    u8 *d = 0, *s = 0;
    u32 i = 0;

    /* Validate user inputs */
    if(!dst.base || !src.base) { return fce_mem_memmove_nullptr; }
    if(src.count > dst.count) { return fce_mem_memmove_smaller; }

    d = (u8*)dst.base;
    s = (u8*)src.base;

    /* If they are the exact same memory address, do nothing */
    if (d == s) { return fce_success; }

    if (d < s) {
        /* Destination is before Source. Copy forwards (left-to-right) */
        for (i = 0; i < src.count; ++i) {
            d[i] = s[i];
        }
    } else {
        /* Destination is after Source. Copy backwards (right-to-left).
         * We do src.count down to 1 to avoid underflowing the unsigned u32 `i` past 0. */
        for (i = src.count; i > 0; --i) {
            d[i - 1] = s[i - 1];
        }
    }

    return fce_success;
}
