#include "fs_private.h"

error_t path_size
(path_t* p, usz* out)
{
    /* Init variables */
    fs_stat_t stats = {0};
    error_t res = success;

    return ((void)(
        /* Check user input and revert to default state */
        (res = (out) ? (*out = 0, success) : null_pointer) ||
        /* Get the stats and get size from that */
        (res = path_stat(p, &stats)) ||
        (*out = (usz)stats.st_size, success)
    ), res);
}
