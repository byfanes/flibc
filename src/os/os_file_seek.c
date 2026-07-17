#include "os_private.h"

#if SYS_OS == SYS_OS_LINUX

error_t __os_file_seek
(os_fid_t handle, usz off, os_seek_type_t type, usz *out)
{
    /* Init variables */
    ssz ret = 0;
    
    /* Set it to default */
    *out = 0;
    
    /* Check the type is valid */
    switch (type) {
        case os_seek_set: case os_seek_cur: case os_seek_end: break;
        default: return invalid_argument;
    }

    ret = syscall_3_linux(syscall_lseek, handle, (ssz)off, (ssz)type);

    /* Check the return */
    if(0 > ret && ret >= -MAX_ERRNO) { return __os_error_map(ret); }

    *out = (usz)ret;
    return success;
}

#else /* End - SYS_OS_LINUX */
#error "The current platform does not have a backend yet!"
#endif /* SYS_OS */
