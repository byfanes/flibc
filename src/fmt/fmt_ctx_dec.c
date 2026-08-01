#include "fmt_private.h"

fmt_status_t __fmt_ctx_dec
(fmt_ctx_t *ctx, i64 dec)
{
    char buf[FLIBC_FMT_TMP_BUF_SIZE];
    char *end = buf + sizeof(buf);
    u64 udec = 0;
    bool is_neg = false;

    udec = (dec < 0) ? (is_neg = true, (u64)(-(dec + 1)) + 1) : (u64)dec;

    do {
        *--end = (char)(udec % 10) + '0';
        udec /= 10;
    } while(udec);

    if(is_neg) { *--end = '-'; }
    return fmt_ctx_print(ctx, end, (u64)(buf + sizeof(buf) - end));
}
