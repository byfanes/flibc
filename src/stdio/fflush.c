#include "stdio_private.h"

error_t fflush
(file_t* _Nullable file)
{
    /* Init variables */
    ssize_t ret = 0;
    usize_t count = 0;

    /* Validate user inputs */
    if(!file) { return null_pointer; }
    if(file->type == file_read) { return io_invalid_op; }

    /* Store count */
    count = file->count;
    file->count = 0;

    /* Call write syscall */
    ret = syscall_3_linux(syscall_write, (ssize_t)file->fd, (ssize_t)file->buf, (ssize_t)count);

    /* Check return of the syscall */
    if(ret < 0) { return io_error; }
    if(ret != (ssize_t)count) { return io_partial; }

    return success;
}
