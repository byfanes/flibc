#include "io_private.h"

error_t io_open
(allocator_t* alloc, const char* name, file_t** out, file_type_t type)
{
    /* Init variables */
    error_t res = success;
    ssz fd = 0, flags = O_CLOEXEC;

    /* Validate user inputs */
    if(!alloc || !name || !out) { return null_pointer; }

    /* Set flags */
    switch(type) {
        case file_read: { flags |= O_RDONLY; } break;
        case file_write: { flags |= O_WRONLY | O_CREAT | O_TRUNC; } break;
        case file_append: { flags |= O_WRONLY | O_CREAT | O_APPEND; } break;
        case file_read_plus: { flags |= O_RDWR; } break;
        case file_write_plus: { flags |= O_RDWR | O_CREAT | O_TRUNC; } break;
        case file_append_plus: { flags |= O_RDWR | O_CREAT | O_APPEND; } break;
        default: { return invalid_argument; }
    }

    /* Call read syscall */
    fd = syscall_3_linux(syscall_open, (ssz)name, flags, 0666);

    /* Check return of the syscall */
    if(fd < 0) { return io_error; }

    /* Allocate new memory for the struct */
    if((res = mem_alloc(alloc, out, sizeof(file_t)))) {
        /* We dont check this syscall because functions has already failed
         * and close will be handled via kernel if open returns a succes
         * closing should not be a problem
         */
        syscall_1_linux(syscall_close, fd);
        return res;
    }

    /* Set variables */
    (*out)->fd = fd;
    (*out)->count = 0;
    (*out)->type = type;
    (*out)->mutex.state = 0;

    return res;
}
