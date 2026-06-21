#include "io_private.h"

error_t io_getpos
(file_t* file, usz* pos)
{
    /* Redirect because its an alternative function which we dont fully support yet. */
    return io_tell(file, pos);
}
