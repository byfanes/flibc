#include "fs_private.h"

error_t is_path_absolute
(path_t* p, bool* out)
{
    /* Check inputs */
    if(!p || !p->items || !p->count || !out) { return null_pointer; }
    *out = (p->items[0] == '/');
    return success;
}
