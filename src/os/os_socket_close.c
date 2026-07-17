#include "os_private.h"

#if SYS_OS == SYS_OS_LINUX

error_t __os_socket_close
(os_sid_t *sid)
{
    /* Init variables */
    ssz ret = 0;
    os_sid_t s = *sid;

    /* Set it to default value */
    *sid = 0;

    /* Ask kernel to close the socket descriptor */
    ret = syscall_1_linux(syscall_close, s);

    /* Check the return */
    if (ret < 0 && ret >= -MAX_ERRNO)
    { return __os_error_map(ret); }

    return success;
}

#else /* End - SYS_OS_LINUX */
#error "The current platform does not have a backend yet!"
#endif /* SYS_OS */
