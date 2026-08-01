#include "fmt_private.h"

fmt_status_t __fmt_ctx_bool
(fmt_ctx_t *ctx, bool b)
{
    const u64 count = ((b) ? sizeof "true" : sizeof "false") - 1;
    const char *cstr = (b) ? "true" : "false";

    return fmt_ctx_print(ctx, cstr, count);
}

fmt_status_t __fmt_ctx_Bool
(fmt_ctx_t *ctx, bool b)
{
    const u64 count = ((b) ? sizeof "True" : sizeof "False") - 1;
    const char *cstr = (b) ? "True" : "False";

    return fmt_ctx_print(ctx, cstr, count);
}

fmt_status_t __fmt_ctx_BOOL
(fmt_ctx_t *ctx, bool b)
{
    const u64 count = ((b) ? sizeof "TRUE" : sizeof "FALSE") - 1;
    const char *cstr = (b) ? "TRUE" : "FALSE";

    return fmt_ctx_print(ctx, cstr, count);
}
