#include "stdio_private.h"

error_t fread
(file_t* file, slice(u8) buf, u32* _Nullable read_count)
{
    /* Init variables */
    ssize_t ret = 0;

    /* Validate user inputs */
    if(!file) { return null_pointer; }
    if(!buf.count || !buf.base) { return null_pointer; }
    if(file->type == file_write || file->type == file_append) { return io_invalid_op; }

    /* Call read syscall */
    ret = syscall_3(syscall_read, file->fd, (ssize_t)buf.base, (ssize_t)buf.count);

    /* Check return of the syscall */
    if(ret < 0) { return io_error; }
    if(read_count) { *read_count = (u32)ret; }
    if(ret < (ssize_t)buf.count) { return io_partial; }

    return success;
}

