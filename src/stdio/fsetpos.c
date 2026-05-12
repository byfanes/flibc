#include "stdio_private.h"

fc_error_t fsetpos
(file_t* file, usize_t pos)
{
    /* Redirect because its an alternative function which we dont fully support yet. */
    return fseek(file, pos, seek_set, nullptr);
}
