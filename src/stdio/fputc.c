#include "stdio_private.h"

fc_error_t fputc
(file_t* file, uint8_t c)
{
    /* Make a little slice and pass it to fwrite function which takes care of everything. */
    slice_t sl = { &c, 1};
    return fwrite(file, sl);
}
