#include "memory_private.h"
#include "error.h"

error_t __memset
(void* dst, usize_t el_size, u8 c)
{
    /* Init variable */
    slice(u8) *dsl = dst;
    u32 i = 0;

    /* Validate user inputs - elsize can be given 0 */
    if(!dsl || !dsl->base) { return null_pointer;}
    if(!el_size) { return elsize_zero;}

    /* Iter 'i' times on the slice's base and set to 'c' */
    for(; i < dsl->count * el_size; ++i) { dsl->base[i] = c; }

    return success;
}
