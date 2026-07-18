#include "process_private.h"

/* This function expects null terminated string */
error_t system_run_cstr_envp
(const char* cmd, const char** envp)
{
    /* Check input and pass to os layer */
    return (!cmd || !envp) ? null_pointer : __os_system_exec((ccstr_t)cmd, (ccstr_t *)envp);
}
