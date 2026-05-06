#include "stdio_private.h"

fc_error_t fopen_stderr
(file_t** out)
{
    /* Init variables */
    fc_error_t res = fce_success;

    /* Validate user inputs */
    if(!out) { return fce_fopen_out_nullptr; }

    /* Allocate new memory for the struct */
    res = malloc(sizeof(file_t), out);
    if(res) { return res; }

    /* Set variables */
    (*out)->fd = UNIX_STDERR;
    (*out)->count = 0;
    (*out)->type = file_write;

    return res;
}
