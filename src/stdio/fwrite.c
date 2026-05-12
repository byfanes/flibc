#include "stdio_private.h"

fc_error_t fwrite
(file_t* file, slice(u8) sl)
{
    /* Init variables */
    fc_error_t res = fce_success;
    ssize_t ret = 0;
    slice(u8) dst = {0};

    /* Validate user inputs */
    if(!file) { return fce_null_pointer; }
    if(!sl.base || !sl.count) { return fce_success; }
    if(file->type == file_read) { return fce_io_invalid_op; }

    /* If it does not fit to buffer fflush then write it */
    if (file->count >= FLIBC_STACK_THRESHOLD)
    {
        res = fflush(file);
        if(res) { return res; }

        /* Call write syscall */
        ret = syscall_3(syscall_write, (ssize_t)file->fd, (ssize_t)sl.base, (ssize_t)sl.count);

        /* Check return of the syscall */
        if(ret < 0) { return fce_io_error; }
        if(ret != (ssize_t)sl.count) { return fce_io_partial; }

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
