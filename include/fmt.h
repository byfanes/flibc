#ifndef __FLIBC_FMT_H__
#define __FLIBC_FMT_H__

/* Note: This module is the most macro heavy part of the library and error message
 * can be messy and if the user enabled a lot warning including unused value and
 * waring as errors most of the errors will came from the unused value (void) solves
 * this if the value will be discarded. Second option it can be about if the user
 * did not use the 'use_fmt_ctx' this will result with a bunch of errors in the compilation
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "base.h"
#include "error.h"
#include "memory.h"
#include "string.h"
#include "require.h"
/* Note "io.h" is included in the implamentation to save a little
 * bit of time while including this header because the only dependency
 * for this header is file_t pointer
 */

#define __FMT_CTX_NAME__ __fmt_ctx

/* Formater setters - User can make their own formats by passing function and variable names */
#define fmt_arg_1(func, a) \
   "") || func(&__FMT_CTX_NAME__, a) || __fmt_ctx_cstr(&__FMT_CTX_NAME__, ""

#define fmt_arg_2(func, a, b) \
   "") || func(&__FMT_CTX_NAME__, a, b) || __fmt_ctx_cstr(&__FMT_CTX_NAME__, ""

#define fmt_arg_3(func, a, b, c) \
   "") || func(&__FMT_CTX_NAME__, a, b, c) || __fmt_ctx_cstr(&__FMT_CTX_NAME__, ""

#define fmt_arg_4(func, a, b, c, d) \
   "") || func(&__FMT_CTX_NAME__, a, b, c, d) || __fmt_ctx_cstr(&__FMT_CTX_NAME__, ""

#define fmt_arg_5(func, a, b, c, d, e) \
   "") || func(&__FMT_CTX_NAME__, a, b, c, d, e) || __fmt_ctx_cstr(&__FMT_CTX_NAME__, ""

/* Public formatters */
/* TODO: #define arg_fp(num)      fmt_arg_1(__fmt_ctx_fp, num) */
#define arg_hex(num)        fmt_arg_2(__fmt_ctx_hex, num, false)
#define arg_HEX(num)        fmt_arg_2(__fmt_ctx_hex, num, true)
#define arg_ptr(ptr)        fmt_arg_1(__fmt_ctx_ptr, ptr)
#define arg_oct(num)        fmt_arg_1(__fmt_ctx_oct, num)
#define arg_dec(num)        fmt_arg_1(__fmt_ctx_dec, num)
#define arg_udec(num)       fmt_arg_1(__fmt_ctx_udec, num)
#define arg_str(str)        fmt_arg_1(__fmt_ctx_str, str)
#define arg_sl(sl)          fmt_arg_2(__fmt_ctx_sl, sl, (require_sl_type(sl), sizeof((sl)->items[0])))
#define arg_cstr(cstr)      fmt_arg_1(__fmt_ctx_cstr, cstr)
#define arg_buf(str, len)   fmt_arg_2(__fmt_ctx_buf, str, len)
#define arg_str_lit(cstr)   fmt_arg_2(__fmt_ctx_buf, cstr, sizeof(cstr) - 1)
#define arg_bool(b)         fmt_arg_1(__fmt_ctx_bool, b)
#define arg_Bool(b)         fmt_arg_1(__fmt_ctx_Bool, b)
#define arg_BOOL(b)         fmt_arg_1(__fmt_ctx_BOOL, b)

/* Note: This is a private field user does not need this */
enum __fmt_ctx_type_e {
    __fmt_ctx_type_unknown = 0,
    __fmt_ctx_type_io,
    __fmt_ctx_type_buf,
    __fmt_ctx_type_sl,
    __fmt_ctx_type_str
};

enum fmt_status_e {
    fmt_continue = false,
    fmt_stop = true
};

typedef enum __fmt_ctx_type_e __fmt_ctx_type_t;
typedef enum fmt_status_e fmt_status_t;
typedef struct fmt_ctx_s fmt_ctx_t;
#define use_fmt_ctx fmt_ctx_t __FMT_CTX_NAME__ = {0}
struct file_s;

/* Note: the wrote count only increases for succesfully written block
 *       And wrote amount increases with the blocks' character amount
 *       block are simplest form of writing and every fmt function is a
 *       one block such as 'arg_dec(32)' is a one block for another example
 *       'fmt_io(io, " Start :" arg_dec(32) " end")' has 3 block
 */
struct fmt_ctx_s {
    __fmt_ctx_type_t type;
    error_t code;
    u64 wrote;
    union {
        struct file_s *io;
        str_t *str;
        sl_u8_t sl;
    } as;
};

/* Note: wrote_out parameters expect a l-value */
/* Note: Do not try to groupexprmacros it will cause a strange behavior */

#define __fmt_ctx_set_buf(buf_ptr, buf_count) \
(__fmt_ctx_set(&__FMT_CTX_NAME__, __fmt_ctx_type_buf, buf_ptr, buf_count))

#define __fmt_ctx_set_sl(sl) \
(require_sl_type(sl), __fmt_ctx_set(&__FMT_CTX_NAME__, __fmt_ctx_type_sl, sl, sizeof((sl)->items[0])))

#define __fmt_ctx_set_str(str) \
(require_typed_ptr(str, str_t), __fmt_ctx_set(&__FMT_CTX_NAME__, __fmt_ctx_type_str, str, NULL))

#define __fmt_ctx_set_io(io) \
(require_typed_incom_ptr(io, struct file_s), __fmt_ctx_set(&__FMT_CTX_NAME__, __fmt_ctx_type_io, io, NULL))

#define __fmt_ret() (__FMT_CTX_NAME__.code)
#define __fmt_ret_wrote(wrote_out) (wrote_out = __FMT_CTX_NAME__.wrote, __FMT_CTX_NAME__.code)

/* IO - File */
#define fmt_io(io, expr) \
((void)(__fmt_ctx_set_io(io) || __fmt_ctx_cstr(&__FMT_CTX_NAME__, ""expr"")), __fmt_ret())

#define fmt_io_wrote(io, wrote_out, expr) \
((void)(__fmt_ctx_set_io(io) || __fmt_ctx_cstr(&__FMT_CTX_NAME__, ""expr"")), __fmt_ret_wrote(wrote_out))

#define fmt_io_nl(io, expr) \
((void)(__fmt_ctx_set_io(io) || __fmt_ctx_cstr(&__FMT_CTX_NAME__, ""expr"\n")), __fmt_ret())

#define fmt_io_wrote_nl(io, wrote_out, expr) \
((void)(__fmt_ctx_set_io(io) || __fmt_ctx_cstr(&__FMT_CTX_NAME__, ""expr"\n")), __fmt_ret_wrote(wrote_out))

/* Slices */
#define fmt_sl(sl, expr) \
((void)(__fmt_ctx_set_sl(sl) || __fmt_ctx_cstr(&__FMT_CTX_NAME__, ""expr"")), __fmt_ret())

#define fmt_sl_wrote(sl, wrote_out, expr) \
((void)(__fmt_ctx_set_sl(sl) || __fmt_ctx_cstr(&__FMT_CTX_NAME__, ""expr"")), __fmt_ret_wrote(wrote_out))

#define fmt_sl_nl(sl, expr) \
((void)(__fmt_ctx_set_sl(sl) || __fmt_ctx_cstr(&__FMT_CTX_NAME__, ""expr"\n")), __fmt_ret())

#define fmt_sl_wrote_nl(sl, wrote_out, expr) \
((void)(__fmt_ctx_set_sl(sl) || __fmt_ctx_cstr(&__FMT_CTX_NAME__, ""expr"\n")), __fmt_ret_wrote(wrote_out))

/* Strings */
#define fmt_str(str, expr) \
((void)(__fmt_ctx_set_str(str) || __fmt_ctx_cstr(&__FMT_CTX_NAME__, ""expr"")), __fmt_ret())

#define fmt_str_wrote(str, wrote_out, expr) \
((void)(__fmt_ctx_set_str(str) || __fmt_ctx_cstr(&__FMT_CTX_NAME__, ""expr"")), __fmt_ret_wrote(wrote_out))

#define fmt_str_nl(str, expr) \
((void)(__fmt_ctx_set_str(str) || __fmt_ctx_cstr(&__FMT_CTX_NAME__, ""expr"\n")), __fmt_ret())

#define fmt_str_wrote_nl(str, wrote_out, expr) \
((void)(__fmt_ctx_set_str(str) || __fmt_ctx_cstr(&__FMT_CTX_NAME__, ""expr"\n")), __fmt_ret_wrote(wrote_out))

/* Buffers */
#define fmt_buf(ptr, count, expr) \
((void)(__fmt_ctx_set_buf(ptr, count) || __fmt_ctx_cstr(&__FMT_CTX_NAME__, ""expr"")), __fmt_ret())

#define fmt_buf_wrote(ptr, count, wrote_out, expr) \
((void)(__fmt_ctx_set_buf(ptr, count) || __fmt_ctx_cstr(&__FMT_CTX_NAME__, ""expr"")), __fmt_ret_wrote(wrote_out))

#define fmt_buf_nl(ptr, count, expr) \
((void)(__fmt_ctx_set_buf(ptr, count) || __fmt_ctx_cstr(&__FMT_CTX_NAME__, ""expr"\n")), __fmt_ret())

#define fmt_buf_wrote_nl(ptr, count, wrote_out, expr) \
((void)(__fmt_ctx_set_buf(ptr, count) || __fmt_ctx_cstr(&__FMT_CTX_NAME__, ""expr"\n")), __fmt_ret_wrote(wrote_out))

/* This function is avaible in this header because if user wants to define
 * their types they should use this function to print that to the target
 */
fmt_status_t fmt_ctx_print(fmt_ctx_t *ctx, const void *ptr, u64 count);

/* Those fmtters are private and shall not accessed directly */
fmt_status_t __fmt_ctx_hex(fmt_ctx_t *ctx, u64 hex, bool use_capital);
fmt_status_t __fmt_ctx_ptr(fmt_ctx_t *ctx, const void *ptr);
fmt_status_t __fmt_ctx_oct(fmt_ctx_t *ctx, u64 oct);
fmt_status_t __fmt_ctx_dec(fmt_ctx_t *ctx, i64 dec);
fmt_status_t __fmt_ctx_udec(fmt_ctx_t *ctx, u64 udec);
/* TODO: fmt_status_t __fmt_ctx_fp(fmt_ctx_t *ctx, double fp); */
fmt_status_t __fmt_ctx_cstr(fmt_ctx_t *ctx, const char *str);
fmt_status_t __fmt_ctx_sl(fmt_ctx_t *ctx, const void *sl, u64 el_size);
fmt_status_t __fmt_ctx_buf(fmt_ctx_t *ctx, const void *buf, u64 len);
fmt_status_t __fmt_ctx_str(fmt_ctx_t *ctx, const str_t *str);
fmt_status_t __fmt_ctx_bool(fmt_ctx_t *ctx, bool b);
fmt_status_t __fmt_ctx_Bool(fmt_ctx_t *ctx, bool b);
fmt_status_t __fmt_ctx_BOOL(fmt_ctx_t *ctx, bool b);

/* This function shall not accessed directly only via the macros */
/* Note: for io and str types count is not used but for slices it acts
 * like el_size and for buf its passed as a count to make an u8 slice
 */
fmt_status_t  __fmt_ctx_set(fmt_ctx_t *ctx, __fmt_ctx_type_t type, void *ptr, u64 count);

#ifdef __cplusplus
}
#endif

#endif /* __FLIBC_FMT_H__ */
