#include "memory_private.h"

error_t __mem_copy_sl
(void *dst, const void *src, usz el_size)
{
    /* Init variables */
    sl_u8_t *dsl = (sl_u8_t *)dst;
    const sl_u8_t *ssl = (const sl_u8_t *)src;

    return
        /* Validate user inputs - items checked in mem_copy_raw */
        (!dsl || !ssl) ? null_pointer :
        /* This should not happen but we check it just in case */
        (dsl == ssl) ? success :
        (ssl->count > dsl->count) ? small_buffer :
        (!el_size) ? elsize_zero :
        mem_copy_raw(dsl->items, ssl->items, ssl->count * el_size);
}
