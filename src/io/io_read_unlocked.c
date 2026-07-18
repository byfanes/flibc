#include "io_private.h"

error_t __io_read_unlocked
(file_t* file, void* buf_ptr, usz amount, usz* read_count)
{
    /* Init variables */
    error_t res = success;

    return ((void)(
        /* Set read_count to default state */
        (*read_count = 0, success) ||
        /* Validate user inputs */
        (res = (!(file->type == file_write || file->type == file_append)) ? success : io_invalid_op) ||
        /* Call read */
        (res = __os_file_read(file->fid, buf_ptr, amount, read_count))
    ), res);
}
