#include "fs_private.h"

fc_error_t path_mtime
(path_t* p, time_t* out)
{
    /* Init variables */
    fs_stat_t stats = {0};
    fc_error_t res = fce_success;

    /* Call stats to get size and checking is done here */
    if(!out) { return fce_null_pointer; }
    if((res = path_stat(p, &stats))) { return res; }
    
    out->sec  = stats.st_size;
    out->nsec = 0;

    return fce_success;
}
