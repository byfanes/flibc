
#include "os_private.h"

#if SYS_OS == SYS_OS_LINUX

error_t __os_time_now
(os_time_t *out)
{
    /* Init variables */
    ssz ret = 0;

    /* Ask kernel to write time inside the struct */
    ret = syscall_2_linux(syscall_gettime, CLOCK_MONOTONIC, (ssz)out);
    
    /* Check the return */
    if (ret < 0 && ret >= -MAX_ERRNO)
    { return __os_error_map(ret); }

    return success;
}

#else /* End - SYS_OS_LINUX */
#error "The current platform does not have a backend yet!"
#endif /* SYS_OS */
