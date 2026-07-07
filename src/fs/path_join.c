#include "fs_private.h"

error_t path_join
(path_t* path, sl_u8_t* extend)
{
    /* Init variables */
    error_t res = success;
    def_da_t *def = (void*)path;

    return ((void)(
        /* Check use inputs */
        (res = (path && extend && path->items && extend->items) ? success : null_pointer) ||
        /* Grow the string with amount of extend and + 1 for '/' */
        (res = str_grow_if(path, extend->count + 1)) ||
        /* If there is no / at the end of path and start of the extend add / */
        ((((def->count && def->items[def->count - 1] != '/') &&
           (extend->count && extend->items[0] != '/'))
            ? def->items[def->count++] = '/' : (0)), success) ||
        /* Add rest of the extend */
        (res = da_push_sl(path, extend))
    ), res);
}
