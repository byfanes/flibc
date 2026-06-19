#include "memory_private.h"

error_t __memcpy_sl
(void* dst, void* src, usz el_size)
{
    /* Init variables */
    sl_u8_t *dsl = dst, *ssl = src;

    /* Validate user inputs - items checked in memcpy_raw */
    if(!dsl || !ssl) { return null_pointer; }
    if(ssl->count > dsl->count) { return small_buffer; }
    if(!el_size) { return elsize_zero; }

    return memcpy_raw(dsl->items, ssl->items, ssl->count * el_size);
}
