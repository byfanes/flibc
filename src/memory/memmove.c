#include "memory_private.h"
#include "error.h"

fc_error_t __memmove
(void* dst, void* src, usize_t el_size)
{
    /* Init variables */
    slice(u8) *dsl = dst, *ssl = src;
    u8 *d = 0, *s = 0;
    usize_t i = 0;

    /* Validate user inputs */
    if(!dsl || !ssl || !dsl->base || !ssl->base) { return fce_null_pointer; }
    if(ssl->count > dsl->count) { return fce_small_buffer; }
    if(!el_size) { return fce_elsize_zero; }

    /* Alias for the pointers */
    d = dsl->base;
    s = ssl->base;

    /* If they are the exact same memory address, do nothing */
    if (d == s) { return fce_success; }

    if (d < s) {
        /* Destination is before Source. Copy forwards (left-to-right) */
        for (i = 0; i < ssl->count * el_size; ++i) {
            d[i] = s[i];
        }
    } else {
        /* Destination is after Source. Copy backwards (right-to-left).
         * We do ssl->count * el_size down to 1 to avoid underflowing
         * the unsigned usize_t `i` past 0.
         */
        for (i = ssl->count * el_size; i > 0; --i) {
            d[i - 1] = s[i - 1];
        }
    }

    return fce_success;
}
