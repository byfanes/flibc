#include "string_private.h"

error_t str_formatf
(str_t* base, const char* fmt, ...)
{
    /* Init variables */
    va_list ap;
    error_t res = success;
    usize_t wrote_count = 0;
    def_da_t *def = (void*)base;
    slice(u8) zero_sl = {0};
    slice(u8) fmt_sl = {0};
    slice(u8) base_sl = {0};

    if(!base || !base->items || !fmt) { return null_pointer; }

    set_slice(&fmt_sl, fmt, strlen(fmt));

    /* Start va and format string */
    va_start(ap, fmt);
    if((res = __formatf(zero_sl, fmt_sl, &wrote_count, ap))) { return res; }
    str_grow_if(base, wrote_count);

    /* Set base_sl to start position and ap is still usable because formatf copies it */
    set_slice(&base_sl, &base->items[base->count], wrote_count);
    /* Assume this wont give an error because previous one should have checked it */
    __formatf(base_sl, fmt_sl, &wrote_count, ap);
    def->count += wrote_count;

    /* End va list */
    va_end(ap);

    return res;
}
