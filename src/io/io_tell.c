#include "io_private.h"

error_t io_tell
(file_t* file, usz* out)
{
    /* Redirect to fseek it is safe to use nullptr as out
     * but function does nothing in that case.
     */
    return io_seek(file, 0L, seek_cur, out);
}
