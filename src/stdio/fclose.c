#include "stdio_private.h"

fc_error_t fclose
(file_t** file)
{
    /* Init variables */
    fc_error_t res = fce_success;
    arch_t ret = 0;

    /* Validate user inputs */
    if(!file) { return fce_fclose_nullptr; }
    if(!*file) { return fce_fclose_nullptr; }

    /* Call flush to write the remaing buffer */
    res = fflush(*file);
    if(res) { return res; }

    /* Call close syscall */
    ret = syscall_1(syscall_close, (*file)->fd);

    res = free(file);
    if(res) { return res; }
    
    /* Check return of the syscall */
    if(ret == 0) { return res; } 
    return fce_fclose_failed;
}
