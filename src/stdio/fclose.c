#include "stdio_private.h"

fc_error_t fclose
(file_t** file)
{
    /* Init variables */
    fc_error_t res = fce_success;
    ssize_t ret = 0;

    /* Validate user inputs */
    if(!file) { return fce_null_pointer; }
    if(!*file) { return fce_success; }

    /* Call flush to write the remaing buffer */
    if((*file)->type != file_read) {
        res = fflush(*file);
        if(res) { return res; }
    }

    if(!((*file)-> fd == UNIX_STDERR || (*file)-> fd == UNIX_STDIN || (*file)-> fd == UNIX_STDOUT))
    {
        /* Call close syscall */
        ret = syscall_1(syscall_close, (*file)->fd);

        /* Check return of the syscall */
        if(ret != 0) { return fce_io_error; }
    }

    /* Free the memory back zeroed by the free */
    res = free(file);
    if(res) { return res; }

    return fce_success;
}
