#include "fmt_private.h"

fmt_status_t __fmt_ctx_hex
(fmt_ctx_t *ctx, u64 hex, bool use_capital)
{
    char buf[FLIBC_FMT_TMP_BUF_SIZE];
    char *end = buf + sizeof(buf);
    const char *hex_table = nullptr;
    hex_table = (use_capital) ? "0123456789ABCDEF" : "0123456789abcdef";

    do {
        *--end = hex_table[hex & 15];
        hex >>= 4;
    } while(hex);

    return fmt_ctx_print(ctx, end, (u64)(buf + sizeof(buf) - end));
}
