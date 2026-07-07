#include "string_private.h"

error_t str_copy
(str_t* base, str_t* cpy)
{
    def_da_t *def = (void*)base;

    return
        /* Check input */
        (!base || !cpy || !base->items) ? null_pointer :
        /* Early return if its a null string */
        (!cpy->count || !cpy->items) ? success :
        /* Clean the count and use strcat instead to start from begining*/
        (def->count = 0, str_cat(base, cpy));
}
