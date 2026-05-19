#include "process_private.h"

error_t proc_run
(cmd_t cmd, env_t env)
{
    /* Init variables */
    ssize_t pid = 0, ret = 0;
    int status = 0;

    /* Check input */
    if(!cmd.count || !cmd.items || !env.continues)
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
    for(;;) {
        /* Call wait for checking if the child is finished */
        ret = syscall_4_linux(syscall_wait4, pid, &status, 0, 0);

        /* Soemthing went wrong */
        if(ret < 0) { return proc_child_failed; }

        /* Success */
        if(ret == pid) { break; }
    }

    return success;
}
