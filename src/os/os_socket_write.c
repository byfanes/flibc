#include "os_private.h"

#if SYS_OS == SYS_OS_LINUX

error_t __os_socket_write
(os_sid_t sid, const void *buf, usz count)
{
    /* Init variables */
    ssz ret = 0;

    ret = syscall_3_linux(syscall_write, sid, (ssz)buf, (ssz)count);

    /* Check the return */
    if(ret == 0) { return connection_closed; }
    if (ret < 0 && ret >= -MAX_ERRNO)
    { return __os_error_map(ret); }

    return success;
}

#else /* End - SYS_OS_LINUX */
#error "The current platform does not have a backend yet!"
#endif /* SYS_OS */
