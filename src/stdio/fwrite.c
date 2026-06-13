#include "stdio_private.h"

error_t __fwrite
(file_t* file, void* raw_sl, usize_t el_size)
{
    /* Init variables */
    error_t res = success;
    ssize_t ret = 0;
    sl_u8_t dst = {0};
    sl_u8_t sl = {0};

    /* Validate user inputs */
    if(!file || !raw_sl) { return null_pointer; }
    if(!el_size) { return elsize_zero; }
    set_slice(&sl, ((sl_u8_t*)raw_sl)->items, ((sl_u8_t*)raw_sl)->count * el_size);
    if(!sl.items || !sl.count) { return success; }
    set_slice(&sl, sl.items, sl.count * el_size);
    if(file->type == file_read) { return io_invalid_op; }

    /* If it does not fit to buffer fflush then write it */
    if (sl.count >= FLIBC_STACK_THRESHOLD)
    {
        if((res = fflush(file))) { return res; }

        /* Call write syscall */
        ret = syscall_3_linux(syscall_write, (ssize_t)file->fd, (ssize_t)sl.items, (ssize_t)sl.count);

        /* Check return of the syscall */
        if(ret < 0) { return io_error; }
        if(ret != (ssize_t)sl.count) { return io_partial; }

        return res;
    }

    /* If it fits to buffer by only itself flush - append later  */
    if (sl.count + file->count >= FLIBC_STACK_THRESHOLD && sl.count < FLIBC_STACK_THRESHOLD)
    {
        if((res = fflush(file))) { return res; }
    }

    /* Set dst */
    set_slice(&dst, &file->buf[file->count], FLIBC_STACK_THRESHOLD - file->count);

    /* Copy the new data to buffer */
    if((res = memcpy(&dst, &sl))) { return res; }

    /* Update the count */
    file->count += sl.count;

    return res;
}
