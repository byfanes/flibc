#include "process_private.h"

/* This function expects null terminated string */
error_t system_run_cstr_envp
(const char* cmd, char** envp)
{
    /* Init variables */
    char* argv[4] = {0};
    u32 argc = 0;

    /* Check input */
    if(!cmd) { return null_pointer; }
    if(!envp) { return null_pointer; }

    /* Construct the list */
    argv[argc++] = (void*)"sh";
    argv[argc++] = (void*)"-c";
    argv[argc++] = (void*)cmd;
    argv[argc++] = 0;

    /* Call execve syscall */
    syscall_3_linux(syscall_execve, (ssz)"/usr/bin/sh", (ssz)argv, (ssz)envp);

    /* Execve syscall wont return in success other wise its failed */
    return process_error;
}
