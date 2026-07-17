#include "io_private.h"

error_t __io_flush_unlocked
(file_t* file)
{
    /* Init variables */
    usz count = 0;
    error_t res = success;

    return ((void)(
        /* Check file type */
        (res = (file->type != file_read) ? success : io_invalid_op) ||
        /* Store the count */
        (count = file->count, file->count = 0, success) ||
        /* Call write */
        (res = __os_file_write(file->fd, file->buf, count))
    ), res);
}
