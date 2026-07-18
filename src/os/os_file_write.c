#include "os_private.h"

#if SYS_OS == SYS_OS_LINUX

error_t __os_file_write
(os_fid_t fid, const void *buf, usz count)
{
    /* Init variables */
    ssz ret = 0;
    error_t res = success;
    usz written = 0;
    
    while(written < count) {
        ret = syscall_3_linux(syscall_write, fid,
            (ssz)((ccstr_t)buf + written), (ssz)(count - written));

        if(0 == ret) { return io_partial; }
        if(0 > ret && ret >= -MAX_ERRNO) {
            res = __os_error_map(ret);
            if(res == interrupted) { continue; }
            return res;
        }

        written += (usz)ret;
    }
    
    return success;
}

#else /* End - SYS_OS_LINUX */
#error "The current platform does not have a backend yet!"
#endif /* SYS_OS */
