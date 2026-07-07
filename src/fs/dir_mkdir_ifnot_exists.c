#include "fs_private.h"

error_t dir_mkdir_ifnot_exists
(path_t* path)
{
    /* Init variables */
    error_t res = success;
    bool exists = false;

    /* Check if it exists or not in that case create it */
    return ((void)(
        (res = dir_exists(path, &exists)) ||
        (exists ? (res = success) : (res = dir_mkdir(path)))
    ), res);
}
