#include "os_private.h"

#if SYS_OS == SYS_OS_LINUX

error_t __os_process_wait_any_on_list
(const os_pid_t *list, usz count, const os_pid_t **found, ssz *code)
{
    /* Init variables */
    ssz pid = 0;
    ssz status = 0;
    usz i = 0;

    /* Set it to default state */
    *found = 0;

    /* Find a process which is finished */
    pid = syscall_4_linux(syscall_wait4, -1, (ssz)&status, 0, 0);

    /* Check the return */
    if (pid < 0 && pid >= -MAX_ERRNO)
    { return __os_error_map(pid); }

    /* Find the done pid in the list */
    for(; i < count; ++i, ++list) {
        if(*list == pid) {
            *found = list;
            if (WIFEXITED(status)) {
                *code = WEXITSTATUS(status);
            }
            return success;
        }
    }

    return does_not_exist;
}

#else /* End - SYS_OS_LINUX */
#error "The current platform does not have a backend yet!"
#endif /* SYS_OS */
