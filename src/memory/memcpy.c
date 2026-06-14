#include "memory_private.h"
#include "error.h"

error_t __memcpy
(void* dst, void* src, usz el_size)
{
    /* Init variables */
    sl_u8_t *dsl = dst, *ssl = src;
    u32 i = 0;

    /* Validate user inputs */
    if(!dsl || !ssl || !dsl->items || !ssl->items) { return null_pointer; }
    if(ssl->count > dsl->count) { return small_buffer; }
    if(!el_size) { return elsize_zero; }

    /* Iter 'ssl->count' times on the slices' items and copy to dst from src */
    for(i = 0; i < ssl->count * el_size; ++i) { dsl->items[i] = ssl->items[i]; }
    return success;
}
