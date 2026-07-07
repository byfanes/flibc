#include "memory_private.h"

error_t __mem_cpy_sl
(void* dst, void* src, usz el_size)
{
    /* Init variables */
    sl_u8_t *dsl = dst, *ssl = src;

    return
        /* Validate user inputs - items checked in memcpy_raw */
        (!dsl || !ssl) ? null_pointer :
        (ssl->count > dsl->count) ? small_buffer :
        (!el_size) ? elsize_zero :
        mem_cpy_raw(dsl->items, ssl->items, ssl->count * el_size);
}
