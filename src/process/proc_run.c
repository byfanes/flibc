#include "process_private.h"

error_t proc_run
(cmd_t* cmd, env_t* env)
{
    /* Init variables */
    ssz pid = 0;
    error_t res = success;

    return ((void)(
        (res = (cmd && env && env->vars.items && env->list.items && cmd->items)
             ? success : null_pointer) ||
        (res = ((pid = syscall_0_linux(syscall_fork)) < 0) ? process_error : success) ||
        ((pid != 0) ? (res = waitapid(pid))
                    : (system_run_env(cmd, env), syscall_1_linux(syscall_exit, 1)))
    ), res);
}
