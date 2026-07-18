#include "process_private.h"

error_t proc_spawn_fixed
(cmd_t* cmd, env_t* env, da_proc_t* procs, ssz _Nullable *code)
{
    /* Init variables */
    os_pid_t *pid_loc = nullptr;
    error_t res = success;
    ssz tmp = 0;

    return ((void)(
        /* Check user inputs */
        (res = (procs && env && env->list.items) ? success : null_pointer) ||
        /* Make cmd a c-str */
        (res = str_add_shadow_null(cmd)) ||
        /* Use valid code pointer */
        ((code = (code) ? (*code = 0, code) : &tmp), success) ||
        /* If full wait for a pid to end if there is empty space use that */
        ((procs->count >= procs->capacity)
            ? (res = __os_process_wait_any_on_list(
                procs->items, procs->count,
                (const os_pid_t **)&pid_loc, code))
            : (res = (pid_loc = procs->items + procs->count, success))) ||
        /* Create new process */
        (res = __os_process_spawn(cmd->items, env->list.items, pid_loc))
    ), (void)( /* Clean up */
        /* Update if it used empty slot and not failed */
        ((!res && procs->count < procs->capacity)
             ? (slice_set(procs, procs->items, procs->count + 1)) : (success)),
        /* If failed and waited remove the empty slot to prevent usage again */
        ((res && procs->count >= procs->capacity)
             ? (da_unordered_remove_on_ptr(procs, pid_loc)) : (success))
    ), res);
}
