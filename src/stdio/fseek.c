#include "stdio_private.h"

error_t fseek
(file_t* file, usz off, seek_type_t type, usz* _Nullable out)
{
    /* Init variables */
    int32_t whence = 0;
    ssz ret = 0;

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

    mutex_lock(&file->mutex);
    /* Call lseek syscall */
    ret = syscall_3_linux(syscall_lseek, (ssz)file->fd, (ssz)off, whence);
    mutex_unlock(&file->mutex);

    /* Check return of the syscall */
    if(ret == -1) { return io_error; }
    if(out) { *out = (usz)ret; }

    return success;
}
