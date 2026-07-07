#include "fs_private.h"

error_t path_mtime
(path_t* p, time_t* out)
{
    /* Init variables */
    fs_stat_t stats = {0};
    error_t res = success;

    return ((void)(
        /* Check user inputs and revert to default state */
        (res = (out) ? (out->sec = 0, out->nsec = 0, success) : null_pointer) ||
        /* Get the stats of the file and set the time modifiers */
        (res = path_stat(p, &stats)) ||
        (out->nsec = stats.st_mtime_nsec, success) ||
        (out->sec = stats.st_mtime, success)
    ), res);
}
