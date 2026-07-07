#include "string_private.h"

error_t str_formatf_sl
(str_t* base, sl_u8_t fmt, ...)
{
    /* Init variables */
    va_list ap;
    error_t res = success;
    usz wrote_count = 0;
    def_da_t *def = (void*)base;
    sl_u8_t zero_sl = {0}, base_sl = {0};

    return ((void)(
        /* Check user inputs */
        (res = (base && base->items && fmt.items) ? success : null_pointer) ||
        /* Start va block */
        (va_start(ap, fmt),
            /* Get the amount memory needed first */
            (res = __formatf(zero_sl, fmt, &wrote_count, ap)) ||
            /* Allocate that much of memory if needed */
            (res = str_grow_if(base, wrote_count)) ||
            /* Format the string */
            (res = slice_set(&base_sl, &base->items[base->count], wrote_count)) ||
            (res = __formatf(base_sl, fmt, &wrote_count, ap)),
        va_end(ap), def->count += wrote_count, res)
    ), res);
}
