#include "stdio_private.h"

fc_error_t fread
(file_t* file, slice(u8) buf, u32* _Nullable read_count)
{
    /* Init variables */
    ssize_t ret = 0;

    /* Validate user inputs */
    if(!file) { return fce_null_pointer; }
    if(!buf.count || !buf.base) { return fce_null_pointer; }
    if(file->type == file_write || file->type == file_append) { return fce_io_invalid_op; }

    /* Call read syscall */
    ret = syscall_3(syscall_read, file->fd, (ssize_t)buf.base, (ssize_t)buf.count);

    /* Check return of the syscall */
    if(ret < 0) { return fce_io_error; }
    if(read_count) { *read_count = (u32)ret; }
    if(ret < (ssize_t)buf.count) { return fce_io_partial; }

    return fce_success;
}

