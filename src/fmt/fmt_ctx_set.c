#include "fmt_private.h"

fmt_status_t  __fmt_ctx_set
(fmt_ctx_t *ctx, __fmt_ctx_type_t type, void *ptr, u64 count)
{
    if(!ctx || !ptr) { return fmt_stop; }

    mem_zeroed(ctx);

    /* Buf type uses sl type but it needs a slice construction first */
    ctx->type = (type == __fmt_ctx_type_buf) ? __fmt_ctx_type_sl : type;

    switch(type) {
        default:
        case __fmt_ctx_type_unknown: { __unreachable(); }
        case __fmt_ctx_type_io: {
            ctx->as.io = ptr;
        } break;
        case __fmt_ctx_type_sl: {
            mem_cpy_raw(&ctx->as.sl, ptr, sizeof(ctx->as.sl));
            slice_set(&ctx->as.sl, ctx->as.sl.items, ctx->as.sl.count * count);
        } break;
        case __fmt_ctx_type_str: {
            ctx->as.str = ptr;
        } break;
        case __fmt_ctx_type_buf: {
            slice_set(&ctx->as.sl, ptr, count);
        } break;
    }

    return fmt_continue;
}
