#include "fmt_private.h"

fmt_status_t __fmt_ctx_ptr
(fmt_ctx_t *ctx, const void *ptr)
{
    char buf[FLIBC_FMT_TMP_BUF_SIZE];
    char *end = buf + sizeof(buf);
    const char *hex_table = "0123456789abcdef";
    u64 hex = (uintptr_t)ptr;

    do {
        *--end = hex_table[hex & 15];
        hex >>= 4;
    } while(hex);

    *--end = 'x';
    *--end = '0';

    return fmt_ctx_print(ctx, end, (u64)(buf + sizeof(buf) - end));
}
