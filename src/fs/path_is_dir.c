#include "fs_private.h"

error_t path_is_dir
(path_t* p, bool* out)
{
    /* Init variables */
    error_t res = success;
    fs_stat_t stats = {0};

    /* Check inputs set it to false for failure case */
    if(!out) { return null_pointer; }
    *out = false;

    /* Check if not fail set it */
    if((res = path_stat(p, &stats))) { return res; }
    *out = (stats.st_mode == S_IFDIR);
    
    return success;
}
