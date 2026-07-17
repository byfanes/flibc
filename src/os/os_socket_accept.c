#include "os_private.h"

#if SYS_OS == SYS_OS_LINUX

error_t __os_socket_accept
(os_sid_t sid, os_sid_t *out, os_saddr_t *addr)
{
    /* Init variables */
    ssz ret = 0;
    ssz len = sizeof(*out);

    /* Set it to default value in case of fail */
    *out = 0;

    ret = syscall_3_linux(syscall_accept, sid, (ssz)addr, (ssz)&len);

    /* Check the return */
    if (ret < 0 && ret >= -MAX_ERRNO)
    { return __os_error_map(ret); }

    *out = ret;
    return success;
}

#else /* End - SYS_OS_LINUX */
#error "The current platform does not have a backend yet!"
#endif /* SYS_OS */
