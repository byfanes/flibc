#include "fs_private.h"

fc_error_t dir_mkdir_ifnot_exists
(path_t* path)
{
    /* Init variables */
    fc_error_t res = fce_success;
    bool exists = false;

    /* Check if it exists or not in that case crate it */
    if((res = dir_exists(path, exists))) { return res; }
    if(exists) { return fce_success; }
    return dir_mkdir(path);
}
