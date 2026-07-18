#include "os_private.h"

#if SYS_OS == SYS_OS_LINUX

error_t __os_cwd_set
(os_cstr_t path)
{
    /* Init variables */
    ssz ret = 0;

    /* Ask kernel to change the directory to path */
    ret = syscall_1_linux(syscall_chdir, (ssz)path);

    /* Check the return */
    if(0 > ret && ret >= -MAX_ERRNO) { return __os_error_map(ret); }

    return success;
}

#else /* End - SYS_OS_LINUX */
#error "The current platform does not have a backend yet!"
#endif /* SYS_OS */
