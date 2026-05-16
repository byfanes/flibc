#include "stdio_private.h"

error_t fgetpos
(file_t* file, usize_t* pos)
{
    /* Redirect because its an alternative function which we dont fully support yet. */
    return ftell(file, pos);
}
