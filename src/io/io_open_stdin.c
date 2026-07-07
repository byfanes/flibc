#include "io_private.h"

error_t io_open_stdin
(allocator_t* alloc, file_t** out)
{
    /* Init variables */
    error_t res = success;

    return ((void)(
        /* Validate user inputs */
        (res = (alloc && out) ? success : null_pointer) ||
        /* Allocate new memory for the struct */
        (res = mem_alloc(alloc, out, sizeof(file_t))) ||
        /* Set variables */
        ((*out)->fd = UNIX_STDIN,
         (*out)->count = 0,
         (*out)->type = file_read,
         (*out)->mutex.state = 0, success)
    ), res);
}
