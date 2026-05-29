#include "stdio_private.h"

error_t fputc
(file_t* file, uint8_t c)
{
    /* Make a little slice and pass it to fwrite function which takes care of everything. */
    sl_u8_t sl = {0};
    set_slice(&sl, &c, 1);
    return fwrite(file, &sl);
}
