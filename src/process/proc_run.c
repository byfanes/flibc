#include "process_private.h"

error_t proc_run
(cmd_t *cmd, env_t *env, ssz *exit_code)
{
    /* Init variables */
    ssz tmp = 0;
    error_t res = success;

    return ((void)(
        (res = (env && env->vars.items && env->list.items) ? success : null_pointer) ||
        (res = str_add_shadow_null(cmd)) ||
        (res = __os_process_run((const char *)cmd->items, env->list.items, (exit_code) ? exit_code : &tmp))
    ), res);
}
