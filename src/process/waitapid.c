#include "process_private.h"

error_t waitapid
(ssz pid)
{
    /* Init variables */
    ssz ret = 0;
    int status = 0;

    for(;;) {
        /* Call wait for checking if the child is finished */
        ret = syscall_4_linux(syscall_wait4, pid, (ssz)&status, 0, 0);

        /* Process has been interupted try again */
        if(ret == -EINTR) { continue; }

        /* Something went wrong */
        if(ret < 0) { return proc_child_failed; }

        /* Success */
        if(ret == pid) { return success; }
    }

    /* Function should not reach this part it needs to end in the loop */
    __unreachable();
}
