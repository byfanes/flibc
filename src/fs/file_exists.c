#include "fs_private.h"

error_t file_exists
(path_t* p, bool* out)
{
    /* Init variables */
    bool is_exists = false;
    error_t res = success;

    return ((void)(
        /* Check user inputs and check if there is an entry and if its a file */
        (res = (out) ? success : null_pointer) ||
        (res = path_exists(p, &is_exists)) ||
        ((is_exists) ? (res = path_is_file(p, out))
                     : success)
    ), res);
}
