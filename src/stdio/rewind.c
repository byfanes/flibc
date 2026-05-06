#include "stdio_private.h"

fc_error_t rewind
(file_t* file)
{
    /* Redirect to fseek */
    return fseek(file, 0L, seek_set, nullptr);
}
