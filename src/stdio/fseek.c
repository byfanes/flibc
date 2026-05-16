#include "stdio_private.h"

error_t fseek
(file_t* file, usize_t off, seek_type_t type, usize_t* _Nullable out)
{
    /* Init variables */
    int32_t whence = 0;
    ssize_t ret = 0;

    /* Validate user inputs */
    if(!file) { return null_pointer; }
    if(out) { *out = 0; }

    /* Set flags */
    switch(type) {
        case seek_set: { whence = SEEK_SET; } break;
        case seek_cur: { whence = SEEK_CUR; } break;
        case seek_end: { whence = SEEK_END; } break;
        default: { return invalid_argument; }
    }

    /* Call lseek syscall */
    ret = syscall_3(syscall_lseek, (ssize_t)file->fd, (ssize_t)off, whence);

    /* Check return of the syscall */
    if(ret == -1) { return io_error; }
    if(out) { *out = (usize_t)ret; }

    return success;
}
