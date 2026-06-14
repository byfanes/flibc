#include "stdio_private.h"

error_t fsetpos
(file_t* file, usz pos)
{
    /* Redirect because its an alternative function which we dont fully support yet. */
    return fseek(file, pos, seek_set, nullptr);
}
