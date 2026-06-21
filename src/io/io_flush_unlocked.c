#include "io_private.h"

error_t __io_flush_unlocked
(file_t* file)
{
    /* Init variables */
    ssz ret = 0;
    usz count = 0;
    error_t res = success;

    /* Validate user inputs */
    if(!file) { return null_pointer; }
    if(file->type == file_read) { return io_invalid_op; }

    /* Store count */
    count = file->count;
    file->count = 0;

    /* Call write syscall */
    ret = syscall_3_linux(syscall_write, (ssz)file->fd, (ssz)file->buf, (ssz)count);

    /* Check return of the syscall */
    if(ret < 0) { return io_error; }
    if(ret != (ssz)count) { return io_partial; }
    return res;
}
