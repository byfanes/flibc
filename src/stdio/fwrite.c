#include "stdio_private.h"

error_t fwrite
(file_t* file, slice(u8) sl)
{
    /* Init variables */
    error_t res = success;
    ssize_t ret = 0;
    slice(u8) dst = {0};

    /* Validate user inputs */
    if(!file) { return null_pointer; }
    if(!sl.base || !sl.count) { return success; }
    if(file->type == file_read) { return io_invalid_op; }

    /* If it does not fit to buffer fflush then write it */
    if (file->count >= FLIBC_STACK_THRESHOLD)
    {
        res = fflush(file);
        if(res) { return res; }

        /* Call write syscall */
        ret = syscall_3(syscall_write, (ssize_t)file->fd, (ssize_t)sl.base, (ssize_t)sl.count);

        /* Check return of the syscall */
        if(ret < 0) { return io_error; }
        if(ret != (ssize_t)sl.count) { return io_partial; }

        return res;
    }

    /* If it fits to buffer by only itself flush - append later  */
    if (sl.count + file->count >= FLIBC_STACK_THRESHOLD && file->count < FLIBC_STACK_THRESHOLD)
    {
        res = fflush(file);
        if(res) { return res; }
    }

    /* Set dst */
    set_slice(&dst, &file->buf[file->count], FLIBC_STACK_THRESHOLD - file->count);

    /* Copy the new data to buffer */
    if((res = memcpy(&dst, &sl))) { return res; }

    /* Update the count */
    file->count += sl.count;

    return res;
}
