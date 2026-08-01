#include "fmt_private.h"

fmt_status_t fmt_ctx_print
(fmt_ctx_t *ctx, const void *ptr, u64 count)
{
    sl_u8_t sl = {0}, out_sl = {0};
    error_t res = success;
    ptr = (ptr) ? ptr : (count = sizeof "(nullptr)" - 1, "(nullptr)");

    if(!ctx) {
        /* This should not be reachable because we pass the stack pointer via internals */
        __unreachable();
    }

    res = slice_set(&sl, ptr, count);
    if(res) { ctx->code = res; return fmt_stop; }

    switch (ctx->type) {
        default:
        /* __fmt_ctx_type_buf is converted to __foramt_ctx_type_sl type its
           only needed for the set function
        */
        case __fmt_ctx_type_buf:
        case __fmt_ctx_type_unknown: { __unreachable(); }
        case __fmt_ctx_type_io: {
            res = io_write(ctx->as.io, &sl);
        } break;
        case __fmt_ctx_type_sl: {
            if(ctx->as.sl.count <= ctx->wrote) { ctx->code = small_buffer; return fmt_stop; }
            res = slice_set(&out_sl, ctx->as.sl.items + ctx->wrote, ctx->as.sl.count - ctx->wrote);
            if(res) { ctx->code = res; return fmt_stop; }
            res = mem_cpy(&out_sl, &sl);
        } break;
        case __fmt_ctx_type_str: {
            res = str_cat_sl(ctx->as.str, &sl);
        } break;
    }

    if(res) { ctx->code = res; return fmt_stop; }
    ctx->wrote += count;
    return fmt_continue;
}
