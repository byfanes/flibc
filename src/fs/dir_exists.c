#include "fs_private.h"

error_t dir_exists
(path_t* p, bool* out)
{
    /* Init variables */
    bool is_exists = false;
    error_t res = success;

    return ((void)(
        /* Check the input variables 'p' checked in 'path_exists' and set default of 'out' */
        (res = (out) ? (*out = false, success) : null_pointer) ||
        /* Check the 'p's existence depending on that check if its a directory */
        (res = path_exists(p, &is_exists)) ||
        (is_exists ? (res = path_is_dir(p, out))
                   : (res = success))
    ), res);
}
