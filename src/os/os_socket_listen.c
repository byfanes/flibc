#include "os_private.h"

#if SYS_OS == SYS_OS_LINUX

error_t __os_socket_listen
(os_sid_t sid, usz count)
{
    /* Init variables */
    ssz ret = 0;

    /* Ask kernel to listen the descriptor with a specific amount of max peers */
    ret = syscall_2_linux(syscall_listen, sid, (ssz)count);

    /* Check the return */
    if (ret < 0 && ret >= -MAX_ERRNO)
    { return __os_error_map(ret); }

    return success;
}

#else /* End - SYS_OS_LINUX */
#error "The current platform does not have a backend yet!"
#endif /* SYS_OS */
