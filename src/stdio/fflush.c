#include "stdio_private.h"

error_t fflush
(file_t* _Nullable file)
{
    /* Init variables */
    ssz ret = 0;
    usz count = 0;
    error_t res = success;

    /* Validate user inputs */
    if(!file) { return null_pointer; }
    if(file->type == file_read) { return io_invalid_op; }

    mutex_lock(&file->mutex);

    /* Store count */
    count = file->count;
    file->count = 0;

    /* Call write syscall */
    ret = syscall_3_linux(syscall_write, (ssz)file->fd, (ssz)file->buf, (ssz)count);

    /* Check return of the syscall */
    if(ret < 0) { res = io_error; goto end; }
    if(ret != (ssz)count) { res = io_partial; goto end; }

end:
    mutex_unlock(&file->mutex);
    return res;
}
