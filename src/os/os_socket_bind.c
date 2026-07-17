#include "os_private.h"

#if SYS_OS == SYS_OS_LINUX

error_t __os_socket_bind
(os_sid_t sid, os_saddr_t *addr)
{
    /* Init variables */
    ssz ret = 0;

    /* Ask kernel to bind the socket */
    ret = syscall_3_linux(syscall_bind, sid, (ssz)addr, sizeof(*addr));

    /* Check the return */
    if (ret < 0 && ret >= -MAX_ERRNO)
    { return __os_error_map(ret); }

    return success;
}

#else /* End - SYS_OS_LINUX */
#error "The current platform does not have a backend yet!"
#endif /* SYS_OS */
