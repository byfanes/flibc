#include "process_private.h"

error_t system_run_env
(cmd_t cmd, env_t env)
{
    /* Init variables */
    error_t res = success;
    char* null_envp[] = {0};
    char** envp = null_envp;

    /* Check input and add null byte to end */
    if((res = str_add_shadow_null(&cmd))) { return res; }
    if(env.continues.items) { envp = (char**)env.continues.items; }

    /* Redirect to another system function to handle now on */
    return system_run_cstr_envp((char*)cmd.items, envp);
}
