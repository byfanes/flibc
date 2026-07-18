#include "os_private.h"

#if SYS_OS == SYS_OS_LINUX

error_t __os_dir_create
(os_cstr_t path)
{
    /* Init variables */
    ssz ret = 0;
    
    /* Ask kernel to create new directory */
    ret = syscall_2_linux(syscall_mkdir, (ssz)path, 0755);

    /* Check the return */
    if (ret < 0 && ret >= -MAX_ERRNO)
    { return __os_error_map(ret); }

    return success;
}

#else /* End - SYS_OS_LINUX */
#error "The current platform does not have a backend yet!"
#endif /* SYS_OS */

