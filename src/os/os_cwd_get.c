#include "os_private.h"

#if SYS_OS == SYS_OS_LINUX

error_t __os_cwd_get
(os_outcstr_t path, usz size, usz *wrote)
{
    /* Init variables */
    ssz ret = 0;

    /* Clear the wrote count */
    *wrote = 0;
    
    /* Ask kernel to fill the buffer with the current directory path */
    ret = syscall_2_linux(syscall_getcwd, (ssz)path, (ssz)size);
    
    /* Check the return */
    if(0 > ret && ret >= -MAX_ERRNO) { return __os_error_map(ret); }

    /* Give the user to wrote count */
    /* Note: Linux includes null termination to count but windows does not */
    *wrote = (usz)ret - 1;
    return success;
}

#else /* End - SYS_OS_LINUX */
#error "The current platform does not have a backend yet!"
#endif /* SYS_OS */
