#include "stdio_private.h"

error_t __fclose_unlocked
(file_t** file)
{
    /* Init variables */
    error_t res = success;

    /* Validate user inputs */
    if(!file) { return null_pointer; }
    if(!*file) { return success; }

    /* Call flush to write the remaing buffer */
    if((*file)->type != file_read) {
        if((res = __fflush_unlocked(*file))) { return res; }
    }

    if(!((*file)-> fd == UNIX_STDERR || (*file)-> fd == UNIX_STDIN || (*file)-> fd == UNIX_STDOUT))
    {
        /* Call and check return of close syscall */
        if(0 != syscall_1_linux(syscall_close, (*file)->fd))
        { return io_error; }
    }

    /* Free the memory back zeroed by the free */
    if((res = free(file))) { return res; }

    return res;
}
