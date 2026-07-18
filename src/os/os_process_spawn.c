#include "os_private.h"

#if SYS_OS == SYS_OS_LINUX

error_t __os_process_spawn
(os_cstr_t cmd, os_cstr_t *env, os_pid_t *out)
{
    /* Init variables */
    ssz ret = 0;

    /* Ask kernel create new fork of the program */
    ret = syscall_0_linux(syscall_fork);

    /* Check the return if it fails return directly */
    if (ret < 0 && ret >= -MAX_ERRNO)
    { return __os_error_map(ret); }

    /* ret is the pid now on if its 0 its child process if not
     * and its has a value its parent and has the child pid
     */
     if(ret == 0) {
         __os_system_exec(cmd, env);
         __os_exit(1);
         /* Child should not return */
     }

     *out = ret;
     return success;
}

#else /* End - SYS_OS_LINUX */
#error "The current platform does not have a backend yet!"
#endif /* SYS_OS */
