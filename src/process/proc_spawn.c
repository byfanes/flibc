#include "process_private.h"

error_t proc_spawn
(cmd_t* cmd, env_t* env, da_proc_t* procs)
{
    /* Init variables */
    error_t res = success;
    ssz pid = 0;
    proc_t proc = {0};

    return ((void)(
        (res = (cmd && env && cmd->items && env->list.items
               && procs && procs->items) ? success : null_pointer) ||
        (res = ((pid = syscall_0_linux(syscall_fork)) < 0) ? process_error : success) ||
        ((pid != 0) ? (proc.handle = pid, res = da_push(procs, &proc))
                    : (system_run_env(cmd, env), syscall_1_linux(syscall_exit, 1)))
     ), res);
}
