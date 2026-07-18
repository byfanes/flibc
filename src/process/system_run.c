#include "process_private.h"

error_t system_run
(cmd_t* cmd)
{
    /* Init variables */
    error_t res = success;

    return ((void)(
        (res = str_add_shadow_null(cmd)) ||
        (res = system_run_cstr((char *)cmd->items))
    ), res);
}
