#include "stdio_private.h"

fc_error_t fwrite
(file_t* file, slice_t sl)
{
    /* Init variables */
    fc_error_t res = fce_success;
    arch_t ret = 0;
    slice_t dst = {0};

    /* Validate user inputs */
    if(!file) { return fce_fwrite_nullptr; }
    if(!sl.base || !sl.count) { return fce_success; }

    /* If it does not fit to buffer fflush then write it */
    if (file->count >= FLIBC_STACK_THRESHOLD)
    {
        res = fflush(file);
        if(res) { return res; }

        /* Call write syscall */
        ret = syscall_3(syscall_write, (arch_t)file->fd, (arch_t)sl.base, sl.count);

        /* Check return of the syscall */
        if(ret < 0) { return fce_fflush_failed; }
        if(ret != sl.count) { return fce_fflush_partial; }

        return res;
    }

    /* If it fits to buffer by only itself flush - append later  */
    if (sl.count + file->count >= FLIBC_STACK_THRESHOLD && file->count < FLIBC_STACK_THRESHOLD)
    {
        res = fflush(file);
        if(res) { return res; }
    }

    /* Set dst */
    dst.base = &file->buf[file->count];
    __set_slice_count(dst, FLIBC_STACK_THRESHOLD - file->count);

    /* Copy the new data to buffer */
    res = memcpy(dst, sl);
    if(res) { return res; }

    /* Update the count */
    file->count += sl.count;

    return res;
}
