#include "fs_private.h"

error_t path_is_relative
(path_t* p, bool* out)
{
    /* Check the inputs are valid and if path starts without / its a relative */
    /* Note: Its only for linux right now */
    return (
        (!p || !p->items || !p->count || !out) ? null_pointer :
            (*out = (p->items[0] != '/'), success));
}
