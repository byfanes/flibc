#include "string_private.h"

fc_error_t strcpy
(str_t* base, str_t* cpy)
{
    def_da_t *def = (void*)base;

    /* Check input */
    if(!base || !cpy || !base->items) { return fce_null_pointer; }
    if(!cpy->count || !cpy->items) { return fce_success; }

    /* Clean the count and use strcat instead to start from begining*/
    def->count = 0;
    return strcat(base, cpy);
}
