#include "process_private.h"

static error_t waitapid
(ssize_t pid)
{
    /* Init variables */
    ssize_t ret = 0;
    int status = 0;

    for(;;) {
        /* Call wait for checking if the child is finished */
        ret = syscall_4_linux(syscall_wait4, pid, &status, 0, 0);

        /* Soemthing went wrong */
        if(ret < 0) { return proc_child_failed; }

        /* Success */
        if(ret == pid) { return success; }
    }
    __unreachable();
}

error_t proc_wait
(da(proc_t)* procs)
{
    /* Init variables */
    u32 i = 0;
    error_t res = success;
    error_t out = success;

    /* Check input */
    if(!procs || !procs->items)
    { return null_pointer; }

    for(; i < procs->count; ++i) {
        out = waitapid(procs->items[i].handle);
        if(!res) { res = out; }
    }

    /* Wont give an error because we already use and checked it */
    da_clear(procs);
    return res;
}
