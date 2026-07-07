#include "memory_private.h"
#include "error.h"

error_t __mem_move_sl
(void* dst, void* src, usz el_size)
{
    /* Init variables */
    sl_u8_t *dsl = dst, *ssl = src;

    return
        (!dsl || !ssl) ? null_pointer :
        (!el_size) ? elsize_zero :
        (ssl->count > dsl->count) ? small_buffer :
        mem_move_raw(dsl->items, ssl->items, ssl->count * el_size);
}
