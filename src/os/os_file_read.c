#include "os_private.h"

#if SYS_OS == SYS_OS_LINUX

error_t __os_file_read
(os_fid_t fid, void *buf, usz count, usz *read_count)
{
    /* Init variables */
    ssz ret = 0;

    /* Ask kernel to read the file descriptor */
    ret = syscall_3_linux(syscall_read, fid, (ssz)buf, (ssz)count);

    /* Handle the error case */
    if(0 > ret && ret >= -MAX_ERRNO)
    { *read_count = 0; return __os_error_map(ret); }

    /* Its not an error so assign the read_count */
    *read_count = (usz)ret;
    return (count == (usz)ret) ? success : io_partial;
}

#else /* End - SYS_OS_LINUX */
#error "The current platform does not have a backend yet!"
#endif /* SYS_OS */
