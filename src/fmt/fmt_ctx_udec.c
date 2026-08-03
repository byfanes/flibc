#include "fmt_private.h"

fmt_status_t __fmt_ctx_udec
(fmt_ctx_t *ctx, u64 udec)
{
    char buf[FLIBC_FMT_TMP_BUF_SIZE];
    char *end = buf + sizeof(buf);

    do {
        *--end = (char)(udec % 10 + '0');
        udec /= 10;
    } while(udec);

    return fmt_ctx_print(ctx, end, (u64)(buf + sizeof(buf) - end));
}
