#include "fs_private.h"

error_t dir_exists
(path_t* p, bool* out)
{
    bool is_exists = false;
    error_t res = success;

    /* Check inputs path checked in path_exists function */
    if(!out) { return null_pointer; }

    /* Check if exists if yes then check is it a dir */
    if((res = path_exists(p, &is_exists))) { return res; }
    if(is_exists) { return is_path_dir(p, out); }

    return success;
}
