#include "os_private.h"

#if SYS_OS == SYS_OS_LINUX

error_t __os_socket_read
(os_sid_t sid, void *buf, usz count, usz *read_count)
{
    /* Init variables */
    ssz ret = 0;

    /* Set it to default value */
    *read_count = 0;

    ret = syscall_3_linux(syscall_read, sid, (ssz)buf, (ssz)count);

    *read_count = (usz)ret;

    /* Check the return */
    if(ret == 0) { return connection_closed; }
    if (ret < 0 && ret >= -MAX_ERRNO)
    { return __os_error_map(ret); }

    return success;
}

#else /* End - SYS_OS_LINUX */
#error "The current platform does not have a backend yet!"
#endif /* SYS_OS */
