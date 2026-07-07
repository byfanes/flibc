#include "io_private.h"

error_t __io_flush_unlocked
(file_t* file)
{
    /* Init variables */
    ssz ret = 0;
    usz count = 0;
    error_t res = success;

    return ((void)(
        /* Check file type */
        (res = (file->type != file_read) ? success : io_invalid_op) ||
        /* Store the count */
        (count = file->count, file->count = 0, success) ||
        /* Call write syscall and save the error */
        (ret = syscall_3_linux(syscall_write, file->fd, (ssz)file->buf, (ssz)count), success) ||
        /* Handle error code if its less than zero its error and if its different than count its partial */
        (res = (0 > ret) ? io_error : ((ret == (ssz)count) ? success : io_partial))
    ), res);
}
