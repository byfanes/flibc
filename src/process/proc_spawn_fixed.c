#include "process_private.h"

error_t proc_spawn_fixed
(cmd_t cmd, env_t env, da(proc_t)* procs)
{
    ssize_t pid = 0;
    ssize_t status = 0;
    u32 i = 0;

    if(!procs) { return null_pointer;}

    if(procs->count >= procs->capacity) {
        pid = syscall_4_linux(syscall_wait4, -1, (ssize_t)&status, 0, 0);
        for(i = 0; i < procs->count; ++i) {
            if(procs->items[i].handle == pid) {
                da_unordered_remove(procs, i);
            }
        }
    }

    return proc_spawn(cmd, env, procs);
}
