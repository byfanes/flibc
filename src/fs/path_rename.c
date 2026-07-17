#include "fs_private.h"

error_t path_rename
(path_t* from, path_t* to)
{
    /* Init variables */
    error_t res = success;
    
    return ((void)(
        /* Validate user input and make them c-strings */
        (res = str_add_shadow_null(from)) ||
        (res = str_add_shadow_null(to)) ||
        /* Ask the os layer to rename it */
        (res = __os_path_rename(from->items, to->items))
    ), res);
}
