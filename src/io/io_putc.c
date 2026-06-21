#include "io_private.h"

error_t io_putc
(file_t* file, uint8_t c)
{
    /* Make a little slice and pass it to fwrite function which takes care of everything. */
    sl_u8_t sl = {0};
    slice_set(&sl, &c, 1);
    return io_write(file, &sl);
}
