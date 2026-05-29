#include "fs_private.h"

error_t path_join
(path_t* path, sl_u8_t* extend)
{
    /* Init variables */
    error_t res = success;
    def_da_t *def = (void*)path;

    /* Check inputs */
    if(!path || !extend || !path->items || !extend->items)
    { return null_pointer; }

    /* Check for space and append '/'x */
    if((res = str_grow_if(path, extend->count + 1))) { return res; }
    if(def->count > 0 && def->items[def->count - 1] != '/') {
        def->items[def->count++] = '/';
    }

    return da_push_sl(path, extend);
}
