#include "stdio_private.h"

error_t fputs
(file_t* file, slice(u8) sl)
{
    /* In the library there is no difference between fputs and fwrite */
    return fwrite(file, sl);
}
