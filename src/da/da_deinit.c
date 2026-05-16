#include "da_private.h"

error_t da_deinit
(void* da)
{
    /* Init variables */
    def_da_t *def = da;

    /* Check input */
    if(!def) { return null_pointer; }

    /* Revert stats */
    def->count = 0;
    def->capacity = 0;

    /* Free memory back it sets to zero automaticly */
    return free(&def->items);
}
