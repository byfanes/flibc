#include "fs_private.h"

error_t path_is_dir
(path_t* p, bool* out)
{
    /* Init variables */
    error_t res = success;
    fs_stat_t stats = {0};

    return ((void)(
        /* Validate out input if it exists set it to false(default) state */
        (res = (out) ? (*out = false, success) : null_pointer) ||
        /* Get the stats of the file and check for directory type */
        (res = path_stat(p, &stats)) ||
        (*out = (stats.type == fs_file_directory), success)
    ), res);
}
