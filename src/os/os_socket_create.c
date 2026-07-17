#include "os_private.h"

#if SYS_OS == SYS_OS_LINUX

error_t __os_socket_create
(os_sid_t *sid, u16 family, u16 type, u32 protocol)
{
    /* Init variables */
    ssz ret = 0;

    /* Set it to default for fail cases */
    *sid = 0;

    /* Ask kernel to update the socket protocol */
    ret = syscall_3_linux(syscall_socket, family, type | SOCK_CLOEXEC, protocol);

    /* Check the return */
    if (ret < 0 && ret >= -MAX_ERRNO)
    { return __os_error_map(ret); }

    /* Set user value in success case */
    *sid = ret;
    return success;
}

#else /* End - SYS_OS_LINUX */
#error "The current platform does not have a backend yet!"
#endif /* SYS_OS */
