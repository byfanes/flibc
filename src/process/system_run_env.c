#include "process_private.h"

error_t system_run_env
(cmd_t* cmd, env_t* env)
{
    /* Init variables */
    error_t res = success;
    ccstr_t null_envp[] = {nullptr};
    ccstr_t* envp = (env && env->list.items) ? env->list.items : null_envp;

    return ((void)(
        (res = str_add_shadow_null(cmd)) ||
        (res = __os_system_exec(cmd->items, envp))
    ), res);
}
