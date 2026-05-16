#include "stdio_private.h"

error_t fopen_stdout
(allocator_t* alloc, file_t** out)
{
    /* Init variables */
    error_t res = success;

    /* Validate user inputs */
    if(!alloc || !out) { return null_pointer; }

    /* Allocate new memory for the struct */
    if((res = malloc(alloc, sizeof(file_t), out))) { return res; }

    /* Set variables */
    (*out)->fd = UNIX_STDOUT;
    (*out)->count = 0;
    (*out)->type = file_write;

    return res;
}
