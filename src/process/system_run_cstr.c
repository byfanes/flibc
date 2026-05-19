#include "process_private.h"

/* This function expects null terminated string */
error_t system_run_cstr
(const char* cmd)
{
    /* This is a wrapper function */
    char* envp[] = {0};
    return system_run_cstr_envp(cmd, envp);
}
