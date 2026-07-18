#include "io_private.h"

error_t io_open_stderr
(allocator_t* alloc, file_t** out)
{
    /* Init variables */
    error_t res = success;
    os_fid_t fid;

    return ((void)(
        /* Validate user inputs */
        (res = (alloc && out) ? success : null_pointer) ||
        /* Try getting the std id first to avoid memory allocation on error */
        (res = __os_file_get_std(&fid, os_file_stderr)) ||
        /* Allocate new memory for the struct */
        (res = mem_alloc(alloc, out, sizeof(file_t))) ||
        /* Set variables */
        ((*out)->fid = fid,
         (*out)->count = 0,
         (*out)->type = file_write,
         (*out)->mutex.state = 0, success)
    ), res);
}
