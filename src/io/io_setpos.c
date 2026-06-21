#include "io_private.h"

error_t io_setpos
(file_t* file, usz pos)
{
    /* Redirect because its an alternative function which we dont fully support yet. */
    return io_seek(file, pos, seek_set, nullptr);
}
