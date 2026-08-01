#include "fmt_private.h"

fmt_status_t __fmt_ctx_str
(fmt_ctx_t *ctx, const str_t *str)
{
    return fmt_ctx_print(ctx, str->items, str->count);
}
