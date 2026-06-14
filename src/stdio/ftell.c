#include "stdio_private.h"

error_t ftell
(file_t* file, usz* out)
{
    /* Redirect to fseek it is safe to use nullptr as out
     * but function does nothing in that case.
     */
    return fseek(file, 0L, seek_cur, out);
}
