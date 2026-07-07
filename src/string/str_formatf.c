#include "string_private.h"

error_t str_formatf
(str_t* base, const char* fmt, ...)
{
    /* Init variables */
    va_list ap;
    error_t res = success;
    usz wrote_count = 0;
    def_da_t *def = (void*)base;
    sl_u8_t zero_sl = {0}, fmt_sl = {0}, base_sl = {0};

    return ((void)(
        /* Check user inputs */
        (res = (base && base->items && fmt) ? success : null_pointer) ||
        /* Set format slice from the string */
        (res = slice_set(&fmt_sl, fmt, cstr_len(fmt))) ||
        /* Start va block */
        (va_start(ap, fmt),
            /* Get amount of needed memory */
            (res = __formatf(zero_sl, fmt_sl, &wrote_count, ap)) ||
            /* Allocate needed memory */
            (res = str_grow_if(base, wrote_count)) ||
            (res = slice_set(&base_sl, &base->items[base->count], wrote_count)) ||
            /* Format the string */
            (res = __formatf(base_sl, fmt_sl, &wrote_count, ap)),
        va_end(ap), def->count += wrote_count, res)
    ), res);
}
