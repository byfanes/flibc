#include "stdio_private.h"

fc_error_t fputs
(file_t* file, slice_t sl)
{
    /* In the library there is no difference between fputs and fwrite */
    return fwrite(file, sl);
}
