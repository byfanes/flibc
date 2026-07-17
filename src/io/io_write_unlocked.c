#include "io_private.h"

error_t __io_write_unlocked
(file_t* file, const void* buf, usz n)
{
    /* Init variables */
    error_t res = success;

    return ((void)(
        (res = (file->type != file_read) ? success : io_invalid_op) ||
        (!n) ||
        ((n >= FLIBC_STACK_THRESHOLD)
            ? ((res = __io_flush_unlocked(file)) || (res = __os_file_write(file->fd, buf, n)))
            : (((n + file->count >= FLIBC_STACK_THRESHOLD)
                     ? (res = __io_flush_unlocked(file)) : success) ||
                (res = mem_cpy_raw(&file->buf[file->count], buf, n)) ||
                (file->count += n, success))
        )
    ), res);
}
