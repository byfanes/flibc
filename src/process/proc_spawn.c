#include "process_private.h"

error_t proc_spawn
(cmd_t cmd, env_t env, da(proc_t)* procs)
{
    /* Init variables */
    ssize_t pid = 0;
    proc_t proc = {0};

    /* Check input */
    if(!cmd.count || !cmd.items || !env.continues.items || !procs || !procs->items)
    { return null_pointer; }

    /* Fork it */
    pid = syscall_0_linux(syscall_fork);
    if(pid < 0) { return process_error; }

    /* Child part */
    if(pid == 0) {
        /* Execute the new program handles null and checking */
        system_run_env(cmd, env);

        /* Exec failed */
        syscall_1_linux(syscall_exit, 1);
        __unreachable();
    }

    /* Parent part */
    proc.handle = pid;
    return da_push(procs, &proc);
}
