#include "fmt_private.h"

fmt_status_t __fmt_ctx_buf
(fmt_ctx_t *ctx, const void *buf, u64 len)
{
    return fmt_ctx_print(ctx, buf, len);
}
