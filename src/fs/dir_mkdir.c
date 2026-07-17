#include "fs_private.h"

error_t dir_mkdir
(path_t* path)
{
    /* Init variables */
    error_t res = success;

    return ((void)(
        /* Add null to make it cstr and pass to kernel - checks done in shadow null function */
        (res = str_add_shadow_null(path)) ||
        (res = __os_dir_create(path->items))
    ), res);
}
