#include "io_private.h"

error_t __io_write_unlocked
(file_t* file, void* raw_sl, usz el_size)
{
    /* Init variables */
    error_t res = success;
    ssz ret = 0;
    sl_u8_t dst = {0};
    sl_u8_t sl = {0};

    /* Validate user inputs */
    if(!file || !raw_sl) { return null_pointer; }
    if(!el_size) { return elsize_zero; }
    slice_set(&sl, ((sl_u8_t*)raw_sl)->items, ((sl_u8_t*)raw_sl)->count * el_size);
    if(!sl.items || !sl.count) { return success; }
    slice_set(&sl, sl.items, sl.count * el_size);
    if(file->type == file_read) { return io_invalid_op; }

    /* If it does not fit to buffer fflush then write it */
    if (sl.count >= FLIBC_STACK_THRESHOLD)
    {
        if((res = __io_flush_unlocked(file))) { goto end; }

        /* Call write syscall */
        ret = syscall_3_linux(syscall_write, (ssz)file->fd, (ssz)sl.items, (ssz)sl.count);

        /* Check return of the syscall */
        if(ret < 0) { res = io_error; goto end; }
        if(ret != (ssz)sl.count) { res = io_partial; goto end; }

        goto end;
    }

    /* If it fits to buffer by only itself flush - append later  */
    if (sl.count + file->count >= FLIBC_STACK_THRESHOLD && sl.count < FLIBC_STACK_THRESHOLD)
    {
        if((res = __io_flush_unlocked(file))) { goto end; }
    }

    /* Set dst */
    slice_set(&dst, &file->buf[file->count], FLIBC_STACK_THRESHOLD - file->count);

    /* Copy the new data to buffer */
    if((res = mem_cpy(&dst, &sl))) { goto end; }

    /* Update the count */
    file->count += sl.count;

end:
    return res;
}
