#include "os_private.h"

#if SYS_OS == SYS_OS_LINUX

error_t __os_process_wait
(os_pid_t pid, ssz *exit_code)
{
    /* Init variables */
    ssz ret = 0;
    int status = 0;

    for(;;) {
        ret = syscall_4_linux(syscall_wait4, pid, (ssz)&status, 0, 0);

        /* Process has been interupted try again */
        if(ret == -EINTR) { continue; }

        /* Something went wrong */
        if(ret < 0) { return proc_child_failed; }

        break;
    }

    if (WIFEXITED(status)) {
        *exit_code = WEXITSTATUS(status);
        return success;
    }

    if (WIFSIGNALED(status))
    { return proc_child_signaled; }

    if (WIFSTOPPED(status))
    { return proc_child_stopped; }

    return proc_child_failed;
}

#else /* End - SYS_OS_LINUX */
#error "The current platform does not have a backend yet!"
#endif /* SYS_OS */
