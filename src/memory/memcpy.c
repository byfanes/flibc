#include "memory_private.h"
#include "error.h"

error_t __memcpy
(void* dst, void* src, usize_t el_size)
{
    /* Init variables */
    slice(u8) *dsl = dst, *ssl = src;
    u32 i = 0;

    /* Validate user inputs */
    if(!dsl || !ssl || !dsl->base || !ssl->base) { return null_pointer; }
    if(ssl->count > dsl->count) { return small_buffer; }
    if(!el_size) { return elsize_zero; }

    /* Iter 'ssl->count' times on the slices' bases and copy to dst from src */
    for(i = 0; i < ssl->count * el_size; ++i) { dsl->base[i] = ssl->base[i]; }
    return success;
}
