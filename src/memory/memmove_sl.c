#include "memory_private.h"
#include "error.h"

error_t __memmove_sl
(void* dst, void* src, usz el_size)
{
    /* Init variables */
    sl_u8_t *dsl = dst, *ssl = src;

    /* Validate user inputs - items checked in memmove_raw */
    if(!dsl || !ssl) { return null_pointer; }
    if(ssl->count > dsl->count) { return small_buffer; }
    if(!el_size) { return elsize_zero; }

    /* Move the memory */
    return memmove_raw(dsl->items, ssl->items, ssl->count * el_size);
}
