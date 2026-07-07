#include "io_private.h"

error_t io_open
(allocator_t* alloc, const char* name, file_t** out, file_type_t type)
{
    /* Init variables */
    error_t res = success;
    ssz fd = 0, flags = O_CLOEXEC;

    return ((void)(
        /* Validate user inputs */
        (res = (alloc && name && out) ? success : null_pointer) ||
        /* Set flags */
        (res = (type == file_read) ? (flags |= O_RDONLY, success) :
               (type == file_write) ? (flags |= O_WRONLY | O_CREAT | O_TRUNC, success) :
               (type == file_append) ? (flags |= O_WRONLY | O_CREAT | O_APPEND, success) :
               (type == file_read_plus) ? (flags |= O_RDWR, success) :
               (type == file_write_plus) ? (flags |= O_RDWR | O_CREAT | O_TRUNC, success) :
               (type == file_append_plus) ? (flags |= O_RDWR | O_CREAT | O_APPEND, success) :
                invalid_argument) ||
        /* Allocate new memory for the struct */
        (res = mem_alloc(alloc, out, sizeof(file_t))) ||
        /* Call read syscall */
        (fd = syscall_3_linux(syscall_open, (ssz)name, flags, 0666), success) ||
        /* Check return of the syscall */
        (res = (fd < 0) ? io_error : success) ||
        /* Set variables */
        ((*out)->fd = fd,
         (*out)->count = 0,
         (*out)->type = type,
         (*out)->mutex.state = 0)
     ), (void)( /* Cleanup - free the memory if open fails */
        ((res) ? mem_free(out) : (0))
     ), res);
}
