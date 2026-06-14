#include "stdio_private.h"

error_t __fputs
(file_t* file, void* sl, usz el_size)
{
    /* In the library there is no difference between fputs and fwrite */
    return __fwrite(file, sl, el_size);
}
