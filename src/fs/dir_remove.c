#include "fs_private.h"

error_t dir_remove
(path_t* path)
{
    /* Init variables */
    error_t res = success;

    return ((void)(
        /* Add null to make it cstr and pass to os function
         * checks done in shadow null function
         */
        (res = str_add_shadow_null(path)) ||
        (res = __os_dir_remove(path->items))
    ), res);
}
