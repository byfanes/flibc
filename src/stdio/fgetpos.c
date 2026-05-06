#include "stdio_private.h"

fc_error_t fgetpos
(file_t* file, arch_t* _Nullable pos)
{
    /* Redirect because its an alternative function which we dont fully support yet. */
    return ftell(file, pos);
}
