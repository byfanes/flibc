#include "io_private.h"

error_t __io_seek_unlocked
(file_t* file, usz off, seek_type_t type, usz* out)
{
    /* Init variables */
    i32 whence = 0;
    ssz ret = 0;
    error_t res = success;

    return ((void)(
        /* Set out to default state */
        (*out = 0, success) ||
        /* Set flags and check it if its a vaild flag */
        (res = (type == seek_set) ? (whence = SEEK_SET, success) :
               (type == seek_cur) ? (whence = SEEK_CUR, success) :
               (type == seek_end) ? (whence = SEEK_END, success) :
                   invalid_argument) ||
        /* Call lseek syscall */
        (ret = syscall_3_linux(syscall_lseek, file->fd, (ssz)off, whence), success) ||
        /* Check return of the syscall */
        (res = (0 > ret) ? io_error : (*out = (usz)ret, success))
    ), res);

}
