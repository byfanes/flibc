#include "stdio_private.h"

fc_error_t fopen
(const char* name, file_t** out, file_type_t type)
{
    /* Init variables */
    fc_error_t res = fce_success;
    arch_t fd = 0, flags = 0;

    /* Validate user inputs */
    if(!name) { return fce_fopen_name_nullptr; }
    if(!out) { return fce_fopen_out_nullptr; }

    /* Set flags */
    switch(type) {
        case file_read: { flags = O_RDONLY; } break;
        case file_write: { flags = O_WRONLY | O_CREAT | O_TRUNC; } break;
        case file_append: { flags = O_WRONLY | O_CREAT | O_APPEND; } break;
        case file_read_plus: { flags = O_RDWR; } break;
        case file_write_plus: { flags = O_RDWR | O_CREAT | O_TRUNC; } break;
        case file_append_plus: { flags = O_RDWR | O_CREAT | O_APPEND; } break;
        default: { return fce_fopen_invalid_type; }
    }

    /* Call read syscall */
    fd = syscall_3(syscall_open, (arch_t)name, flags,
    S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

    /* Check return of the syscall */
    if(fd < 0) { return fce_fopen_failed; }

    /* Allocate new memory for the struct */
    res = malloc(sizeof(file_t), out);
    if(res) { return res; }

    /* Set variables */
    (*out)->fd = fd;
    (*out)->count = 0;
    (*out)->type = type;

    return res;
}
