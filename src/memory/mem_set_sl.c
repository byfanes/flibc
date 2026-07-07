#include "memory_private.h"
#include "error.h"

error_t __mem_set_sl
(void* dst, usz el_size, u8 c)
{
    /* Init variable */
    sl_u8_t *dsl = dst;

    return
        (!dsl) ? null_pointer :
        (!el_size) ? elsize_zero :
        mem_set_raw(dsl->items, c, el_size * dsl->count);
}
