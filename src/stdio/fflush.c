#include "stdio_private.h"

fc_error_t fflush
(file_t* _Nullable file)
{
    /* Init variables */
    ssize_t ret = 0;
    usize_t count = 0;

    /* Validate user inputs */
    if(!file) { return fce_null_pointer; }
    if(file->type == file_read) { return fce_io_invalid_op; }

    /* Store count */
    count = file->count;
    file->count = 0;

    /* Call write syscall */
    ret = syscall_3(syscall_write, (ssize_t)file->fd, (ssize_t)file->buf, (ssize_t)count);

    /* Check return of the syscall */
    if(ret < 0) { return fce_io_error; }
    if(ret != (ssize_t)count) { return fce_io_partial; }

    return fce_success;
}
