#include "io_private.h"

error_t io_rewind
(file_t* file)
{
    /* Redirect to fseek */
    return io_seek(file, 0L, seek_set, nullptr);
}
