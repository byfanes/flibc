#include "stdio_private.h"

fc_error_t fopen_stdout
(allocator_t* alloc, file_t** out)
{
    /* Init variables */
    fc_error_t res = fce_success;

    /* Validate user inputs */
    if(!alloc || !out) { return fce_null_pointer; }

    /* Allocate new memory for the struct */
    if((res = malloc(alloc, sizeof(file_t), out))) { return res; }

    /* Set variables */
    (*out)->fd = UNIX_STDOUT;
    (*out)->count = 0;
    (*out)->type = file_write;

    return res;
}
