#include "io_private.h"

error_t io_open_stdout
(allocator_t* alloc, file_t** out)
{
    /* Init variables */
    error_t res = success;
    os_fid_t handle;

    return ((void)(
        /* Validate user inputs */
        (res = (alloc && out) ? success : null_pointer) ||
        /* Try getting the std handle/descriptor first to avoid memory allocation on error */
        (res = __os_file_get_std(&handle, os_file_stdout)) ||
        /* Allocate new memory for the struct */
        (res = mem_alloc(alloc, out, sizeof(file_t))) ||
        /* Set variables */
        ((*out)->fd = handle,
         (*out)->count = 0,
         (*out)->type = file_write,
         (*out)->mutex.state = 0, success)
    ), res);
}
