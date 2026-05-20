#include "fs_private.h"

error_t dir_mkdir_ifnot_exists
(path_t* path)
{
    /* Init variables */
    error_t res = success;
    bool exists = false;

    /* Check if it exists or not in that case create it */
    if((res = dir_exists(path, exists))) { return res; }
    if(exists) { return success; }
    return dir_mkdir(path);
}
