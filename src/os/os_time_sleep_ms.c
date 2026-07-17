#include "os_private.h"

#if SYS_OS == SYS_OS_LINUX

error_t __os_time_sleep_ms
(u64 ms)
{
    /* Init variables */
    os_time_t time = {0};
    ssz ret = 0;

    /* Set time */
    time.sec  = ms / 1000;
    time.nsec = ms % 1000;

    /* Ask kernel to unlink/delete the file at the path */
    ret = syscall_2_linux(syscall_nanosleep, (ssz)&time, (ssz)nullptr);
    
    /* Check the return */
    if (ret < 0 && ret >= -MAX_ERRNO)
    { return __os_error_map(ret); }

    return success;
}

#else /* End - SYS_OS_LINUX */
#error "The current platform does not have a backend yet!"
#endif /* SYS_OS */
