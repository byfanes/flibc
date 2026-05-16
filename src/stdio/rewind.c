#include "stdio_private.h"

error_t rewind
(file_t* file)
{
    /* Redirect to fseek */
    return fseek(file, 0L, seek_set, nullptr);
}
