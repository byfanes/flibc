#include "process_private.h"

error_t proc_spawn_fixed
(cmd_t cmd, env_t env, da_proc_t* procs)
{
    /* Init variables */
    ssz pid = 0;
    ssz status = 0;
    u32 i = 0;

    /* Check input list */
    if(!procs) { return null_pointer;}

    /* If its full find a finished one */
    if(procs->count >= procs->capacity) {
        /* Find a process which is finished */
        pid = syscall_4_linux(syscall_wait4, -1, (ssz)&status, 0, 0);
        if(pid < 0) { return process_error; }
        for(i = 0; i < procs->count; ++i) {
            /* Make a free slot */
            if(procs->items[i].handle == pid) {
                da_unordered_remove(procs, i);
            }
        }
    }

    /* cmd and env checks done here */
    return proc_spawn(cmd, env, procs);
}
