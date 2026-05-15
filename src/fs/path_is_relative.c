#include "fs_private.h"

fc_error_t path_is_relative
(path_t* p, bool* out)
{
    /* Check inputs */
    if(!p || !p->items || !p->count || !out) { return fce_null_pointer; }
    *out = (p->items[0] != '/');
    return fce_success;
}
