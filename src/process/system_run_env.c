#include "process_private.h"

error_t system_run_env
(cmd_t* cmd, env_t* env)
{
    /* Init variables */
    error_t res = success;
    const char* null_envp[] = {nullptr};
    const char** envp = (env && env->list.items) ? env->list.items : null_envp;

    return ((void)(
        (res = str_add_shadow_null(cmd)) ||
        (res = system_run_cstr_envp((char*)cmd->items, envp))
    ), res);
}
