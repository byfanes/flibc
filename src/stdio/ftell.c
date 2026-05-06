#include "stdio_private.h"

fc_error_t ftell
(file_t* file, arch_t* _Nullable out)
{
    /* Redirect to fseek it is safe to use nullptr as out
     * but function does nothing in that case.
     */
    return fseek(file, 0L, seek_cur, out);
}
