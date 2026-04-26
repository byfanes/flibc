#include "stdio_private.h"

fc_error_t fopen
(const char* name, file_t** out)
{
    /* Init variables */
    fc_error_t res = fce_success;
    arch_t fd = 0;

    /* Validate user inputs */
    if(!name) { return fce_fopen_name_nullptr; }
    if(!out) { return fce_fopen_out_nullptr; }

    /* Call read syscall */
    fd = syscall_3(syscall_open, (arch_t)name, O_CREAT | O_RDWR | O_TRUNC , S_IRUSR | S_IWUSR);

    /* Check return of the syscall */
    if(fd < 0) { return fce_fopen_failed; }

    /* Allocate new memory for the struct */
    res = malloc(sizeof(file_t), out);
    if(res) { return res; }

    /* Set variables */
    (*out)->fd = fd;
    (*out)->count = 0;

    return res;
}
