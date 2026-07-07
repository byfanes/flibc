#include "io_private.h"


error_t __io_write_unlocked
(file_t* file, void* buf, usz n)
{
    /* Init variables */
    error_t res = success;
    ssz ret = 0;

    return ((void)(
        (res = (file->type != file_read) ? success : io_invalid_op) ||
        (!n) ||
        ((n >= FLIBC_STACK_THRESHOLD)
            ? ((res = __io_flush_unlocked(file)) ||
                (ret = syscall_3_linux(syscall_write, file->fd, (ssz)buf, (ssz)n), success) ||
                (res = (ret < 0) ? io_error : ((ret != (ssz)n) ? io_partial : success)))
            : (((n + file->count >= FLIBC_STACK_THRESHOLD)
                     ? (res = __io_flush_unlocked(file)) : success) ||
                (res = mem_cpy_raw(&file->buf[file->count], buf, n)) ||
                (file->count += n, success))
        )
    ), res);
}
