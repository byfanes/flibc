#include "fs_private.h"

fc_error_t file_exists
(path_t* p, bool* out)
{
    /* Behavior of the functions are same */
    return path_is_file(p, out);
}
