#include "crt.h"

error_t main
(std_t std)
{
    /* Init variables */
    error_t res = success;
    u32 read_count = 0;
    u8 buf[128] = {0};
    slice(u8) buf_sl = {0};
    slice(u8) write_sl = {0};

    /* Set the buffer slice */
    set_slice(&buf_sl, buf, sizeof(buf));

    for(;;) {
        /* Read from standard input we can ignore io_partial
         * because we give a buffer which is larger than input
         * count so why that exists it exists because while reading
         * a file requested count is given via the slice's count
         */
        res = fread(std.io.in, buf_sl, &read_count);
        if(res && res != io_partial) { return res; }

        /* If we see an '!' just stop the program */
        if(buf_sl.base[0] == '!') { break; }

        /* Write it to standard out */
        set_slice(&write_sl, buf, read_count);
        if((res = fwrite(std.io.out, write_sl))) { return res; }

        /* Flush the standard out it is not mandatory to do because crt
         * will close and flush the standard ios when program exit via main
         */
        if((fflush(std.io.out))) { return res; }
    }
    return res;
}
