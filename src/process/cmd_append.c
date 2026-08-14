#include "process_private.h"
#include "../da/da_private.h"

error_t __cmd_append
(cmd_t *cmd, const void *vsl, usz el_size)
{
    /* Init variables */
    error_t res = success;
    def_da_t *def = (void *)cmd;
    const sl_u8_t *sl = vsl;

    /* Check inputs */
    if(!el_size) { return elsize_zero; }

    if(!cmd || !sl || !cmd->items || !sl->items)
    { return null_pointer; }

    /* Check for space and append '/'x */
    if((res = str_grow_if(cmd, (el_size * sl->count) + 1))) { return res; }
    if(def->count > 0 && def->items[def->count - 1] != ' ') {
        def->items[def->count++] = ' ';
    }

    return __da_push_sl(cmd, el_size, vsl);
}
