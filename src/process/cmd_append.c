#include "process_private.h"
#include "../da/da_private.h"

error_t cmd_append
(cmd_t* cmd, slice(u8)* sl)
{
    /* Init variables */
    error_t res = success;
    def_da_t *def = (void*)cmd;

    /* Check inputs */
    if(!cmd || !sl || !cmd->items || !sl->base)
    { return null_pointer; }

    /* Check for space and append '/'x */
    if((res = str_grow_if(cmd, sl->count + 1))) { return res; }
    if(def->count > 0 && def->items[def->count - 1] != ' ') {
        def->items[def->count++] = ' ';
    }

    return da_push_sl(cmd, sl);
}
