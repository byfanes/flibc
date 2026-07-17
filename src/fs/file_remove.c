#include "fs_private.h"

error_t file_remove
(path_t* path)
{
    /* Init variables */
    error_t res = success;

    return ((void)(
        /* Input checks done in shadow_null function */
        (res = str_add_shadow_null(path)) ||
        /* Remove the file via os layer and get the result */
        (res = __os_file_remove(path->items))
    ), res);
}
