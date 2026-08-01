#include "fmt_private.h"

fmt_status_t __fmt_ctx_oct
(fmt_ctx_t *ctx, u64 oct)
{
    char buf[FLIBC_FMT_TMP_BUF_SIZE];
    char *end = buf + sizeof(buf);
    const char octs[] =  "01234567";

    do {
        *--end = octs[oct & 7];
        oct >>= 3;
    } while(oct);

    return fmt_ctx_print(ctx, end, (u64)(buf + sizeof(buf) - end));
}
