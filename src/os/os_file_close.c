#include "os_private.h"

#if SYS_OS == SYS_OS_LINUX

error_t __os_file_close
(os_fid_t *set)
{
    /* Init variables */
    os_fid_t fid = *set;
    ssz ret = 0;

    /* Set users' handle to invalid */
    *set = OS_INVALID_FILE_HANDLE;

    /* Avoid closing unix's standard io */
    if(fid == UNIX_STDERR || fid == UNIX_STDIN || fid == UNIX_STDOUT)
    { return success; }
    
    /* Ask kernel to close */
    ret = syscall_1_linux(syscall_close, fid);

    /* Check the return */
    if (ret < 0 && ret >= -MAX_ERRNO)
    { return __os_error_map(ret); }

    return success;
}


#else /* End - SYS_OS_LINUX */
#error "The current platform does not have a backend yet!"
#endif /* SYS_OS */
