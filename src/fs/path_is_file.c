#include "fs_private.h"

fc_error_t path_is_file
(path_t* p, bool* out)
{
    /* Init variables */
    fc_error_t res = fce_success;
    fs_stat_t stats = {0};

    /* Check inputs set it to false for failure case */
    if(!out) { return fce_null_pointer; }
    *out = false;

    /* Check if not fail set it */
    if((res = path_stat(p, &stats))) { return res; }
    *out = (stats.st_mode == S_IFREG);
    
    return fce_success;
}
