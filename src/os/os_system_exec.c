#include "os_private.h"

#if SYS_OS == SYS_OS_LINUX

error_t __os_system_exec
(os_cstr_t cmd, os_cstr_t *envp)
{
    /* Init variables */
    ssz ret = 0;
    os_cstr_t args[4] = {(ccstr_t)"sh", (ccstr_t)"-c", nullptr, nullptr};

    args[2] = cmd;

    /* Call execve syscall */
    ret = syscall_3_linux(syscall_execve, (ssz)"/usr/bin/sh", (ssz)args, (ssz)envp);

    /* Execve syscall wont return in success other wise its failed */
    return __os_error_map(ret);
}

#else /* End - SYS_OS_LINUX */
#error "The current platform does not have a backend yet!"
#endif /* SYS_OS */
