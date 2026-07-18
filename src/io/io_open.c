#include "io_private.h"

error_t io_open
(allocator_t* alloc, const char* name, file_t** out, file_type_t type)
{
    /* Init variables */
    error_t res = success;

    return ((void)(
        /* Validate user inputs */
        (res = (alloc && name && out) ? success : null_pointer) ||
        /* Allocate new memory for the struct */
        (res = mem_alloc(alloc, out, sizeof(file_t))) ||
        /* Call open and get the fd - file_type_t check done inside it
         * int cast is for changing enum which should be same and checked before
         */
        (res = __os_file_open(&(*out)->fid, (cstr_t)name, (int)type)) ||
        /* Set variables */
        ((*out)->count = 0,
         (*out)->type = type,
         (*out)->mutex.state = 0)
     ), (void)( /* Cleanup - free the memory if open fails */
        ((res) ? mem_free(out) : (0))
     ), res);
}
