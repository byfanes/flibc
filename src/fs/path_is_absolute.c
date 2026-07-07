#include "fs_private.h"

error_t path_is_absolute
(path_t* p, bool* out)
{
    /* Check the inputs are valid and if path starts with / its a absolute */
    /* Note: Its only for linux right now */
    return (
        (!p || !p->items || !p->count || !out) ? null_pointer :
            (*out = (p->items[0] == '/'), success));
}
