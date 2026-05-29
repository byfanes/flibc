#include "memory_private.h"
#include "error.h"

error_t __memset
(void* dst, usize_t el_size, u8 c)
{
    /* Init variable */
    sl_u8_t *dsl = dst;
    u32 i = 0;

    /* Validate user inputs - elsize can be given 0 */
    if(!dsl || !dsl->items) { return null_pointer;}
    if(!el_size) { return elsize_zero;}

    /* Iter 'i' times on the slice's items and set to 'c' */
    for(; i < dsl->count * el_size; ++i) { dsl->items[i] = c; }

    return success;
}
