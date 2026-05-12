#include "da_private.h"

fc_error_t da_deinit
(void* set)
{
    /* Init variables */
    def_da_t *def = set;

    /* Check input */
    if(!def) { return fce_null_pointer; }

    /* Revert stats */
    def->count = 0;
    def->capacity = 0;

    /* Free memory back it sets to zero automaticly */
    return free(&def->items);
}
