#include "fs_private.h"

error_t file_exists
(path_t* p, bool* out)
{
    /* Behavior of the functions are same */
    return is_path_file(p, out);
}
