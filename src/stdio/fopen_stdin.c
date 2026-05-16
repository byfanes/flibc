#include "stdio_private.h"

error_t fopen_stdin
(allocator_t* alloc, file_t** out)
{
    /* Init variables */
    error_t res = success;

    /* Validate user inputs */
    if(!alloc || !out) { return null_pointer; }

    /* Allocate new memory for the struct */
    if((res = malloc(alloc, sizeof(file_t), out))) { return res; }

    /* Set variables */
    (*out)->fd = UNIX_STDIN;
    (*out)->count = 0;
    (*out)->type = file_read;

    return res;
}
