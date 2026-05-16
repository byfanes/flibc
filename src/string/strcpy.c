#include "string_private.h"

error_t strcpy
(str_t* base, str_t* cpy)
{
    def_da_t *def = (void*)base;

    /* Check input */
    if(!base || !cpy || !base->items) { return null_pointer; }
    if(!cpy->count || !cpy->items) { return success; }

    /* Clean the count and use strcat instead to start from begining*/
    def->count = 0;
    return strcat(base, cpy);
}
