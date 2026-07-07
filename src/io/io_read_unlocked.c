#include "io_private.h"

error_t __io_read_unlocked
(file_t* file, void* buf_ptr, usz amount, usz* read_count)
{
    /* Init variables */
    ssz ret = 0;
    error_t res = success;

    return ((void)(
        /* Set read_count to default state */
        (*read_count = 0, success) ||
        /* Validate user inputs */
        (res = (!(file->type == file_write || file->type == file_append)) ? success : io_invalid_op) ||
        /* Call read syscall */
        (ret = syscall_3_linux(syscall_read, file->fd, (ssz)buf_ptr, (ssz)amount), success) ||
        /* Check return of the syscall and write the number of bytes read */
        (res = (0 > ret) ? io_error
             : (*read_count = (usz)ret, (ret != (ssz)amount) ? io_partial : success))
    ), res);
}
