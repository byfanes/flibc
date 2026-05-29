#include "string_private.h"

error_t str_formatf_sl
(str_t* base, sl_u8_t fmt, ...)
{
    /* Init variables */
    va_list ap;
    error_t res = success;
    usize_t wrote_count = 0;
    def_da_t *def = (void*)base;
    sl_u8_t zero_sl = {0}, base_sl = {0};

    if(!base || !base->items || !fmt.items || !fmt.count) { return null_pointer; }

    /* Start va and format string */
    va_start(ap, fmt);
    if((res = __formatf(zero_sl, fmt, &wrote_count, ap))) { return res; }
    str_grow_if(base, wrote_count);

    /* Set base_sl to start position and ap is still usable because formatf copies it */
    set_slice(&base_sl, &base->items[base->count], wrote_count);
    /* Assume this wont give an error because previous one should have checked it */
    __formatf(base_sl, fmt, &wrote_count, ap);
    def->count += wrote_count;

    /* End va list */
    va_end(ap);

    return res;
}
