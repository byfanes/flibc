#include "fs_private.h"

error_t path_size
(path_t* p, usize_t* out)
{
    /* Init variables */
    fs_stat_t stats = {0};
    error_t res = success;

    /* Call stats to get size and checking is done here */
    if(!out) { return null_pointer; }
    if((res = path_stat(p, &stats))) { return res; }
    
    *out = (usize_t)stats.st_size;

    return success;
}
