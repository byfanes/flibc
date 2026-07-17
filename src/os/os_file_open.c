#include "os_private.h"

#if SYS_OS == SYS_OS_LINUX

error_t __os_file_open
(os_fid_t *set, const char *path, os_file_type_t type)
{
    /* Init variables */
    ssz ret = 0, flags = O_CLOEXEC;
    usz try_count = 0;
    error_t res = success;

    /* Set it to invalid to prevent use */
    *set = OS_INVALID_FILE_HANDLE;

    switch(type)
    {
        case os_file_read: { flags |= O_RDONLY; } break;
        case os_file_write: { flags |= O_WRONLY | O_CREAT | O_TRUNC; } break;
        case os_file_append: { flags |= O_WRONLY | O_CREAT | O_APPEND; } break;
        case os_file_read_plus: { flags |= O_RDWR; } break;
        case os_file_write_plus: { flags |= O_RDWR | O_CREAT | O_TRUNC; } break;
        case os_file_append_plus: { flags |= O_RDWR | O_CREAT | O_APPEND; } break;
        default: { res = invalid_argument; } break;
    }

    if(res) { return res; }

    do {
        /* Ask kernel to open the file */
        ret = syscall_4_linux(syscall_openat, AT_FDCWD, (ssz)path, flags, 0666);

        /* Check the return */
        if(0 > ret && ret >= -MAX_ERRNO) { res = __os_error_map(ret); }
    } while(res != interrupted && try_count++ < MAX_TRY_COUNT);

    /* Set the handle if success */
    if(!res) { *set = ret; }
    return res;
}

#else /* End - SYS_OS_LINUX */
#error "The current platform does not have a backend yet!"
#endif /* SYS_OS */
