#include "fmt_private.h"

fmt_status_t __fmt_ctx_cstr
(fmt_ctx_t *ctx, const char *str)
{
    /* TODO: This will iterate the string twice dont use this */
    /* Note: cstr_len returns zero if c-string is a null pointer and
     *       fmt_ctx_print write "(nullptr)" if the pointer is null
     */
    /* Early skip for conjuction strings */
    if(str && !*str) { return fmt_continue; }

    return fmt_ctx_print(ctx, str, cstr_len(str));
}
