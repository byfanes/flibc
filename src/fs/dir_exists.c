#include "fs_private.h"

error_t dir_exists
(path_t* p, bool* out)
{
    /* Behavior of the functions are same */
    return is_path_dir(p, out);
}

