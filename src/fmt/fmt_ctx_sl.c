#include "fmt_private.h"

fmt_status_t __fmt_ctx_sl
(fmt_ctx_t *ctx, const void *ssl, u64 el_size)
{
    const sl_u8_t zsl = {0};
    const sl_u8_t *sl = (ssl) ? ssl : &zsl;

    return fmt_ctx_print(ctx, sl->items, sl->count * el_size);
}
