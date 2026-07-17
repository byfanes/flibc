#include "process_private.h"

error_t proc_spawn
(cmd_t* cmd, env_t* env, da_proc_t* procs)
{
    /* Init variables */
    error_t res = success;

    return ((void)(
        (res = (env && env->list.items) ? success : null_pointer) ||
        (res = str_add_shadow_null(cmd)) ||
        (res = da_grow_if(procs, 1)) ||
        (res = __os_process_spawn(
            (const char *)cmd->items, env->list.items, (os_pid_t *)(procs->items + procs->count))) ||
        (res = slice_set(procs, procs->items, procs->count + 1))
     ), res);
}
