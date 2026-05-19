#include "stdio_private.h"

error_t fopen
(allocator_t* alloc, const char* name, file_t** out, file_type_t type)
{
    /* Init variables */
    error_t res = success;
    ssize_t fd = 0, flags = 0;

    /* Validate user inputs */
    if(!alloc || !name || !out) { return null_pointer; }

    /* Set flags */
    switch(type) {
        case file_read: { flags = O_RDONLY; } break;
        case file_write: { flags = O_WRONLY | O_CREAT | O_TRUNC; } break;
        case file_append: { flags = O_WRONLY | O_CREAT | O_APPEND; } break;
        case file_read_plus: { flags = O_RDWR; } break;
        case file_write_plus: { flags = O_RDWR | O_CREAT | O_TRUNC; } break;
        case file_append_plus: { flags = O_RDWR | O_CREAT | O_APPEND; } break;
        default: { return invalid_argument; }
    }

    /* Call read syscall */
    fd = syscall_3_linux(syscall_open, (ssize_t)name, flags,
    S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

    /* Check return of the syscall */
    if(fd < 0) { return io_error; }

    /* Allocate new memory for the struct */
    if((res = malloc(alloc, sizeof(file_t), out))) { return res; }

    /* Set variables */
    (*out)->fd = fd;
    (*out)->count = 0;
    (*out)->type = type;

    return res;
}
