#ifndef __FLIBC_STDIO_H__
#define __FLIBC_STDIO_H__

#include "error.h"
#include "stdtypes.h"
#include "memory.h"
#include "stdarg.h"

struct file_s {
    uint32_t fd;
};

typedef struct file_s file_t;

can_be_slice(char);

static inline def_slice_t _fmt_from_str(const char* str) {
    uint32_t i = 0;
    while(str[i++]);
    return (def_slice_t){ .base = (byte_t*)str, .count = i - 1 };
}

static inline def_slice_t _fmt_from_slice(def_slice_t slice) {
    return slice;
}

#define FORMAT_TO_SLICE(fmt) _Generic((fmt), \
    char *:       _fmt_from_str, \
    const char *: _fmt_from_str, \
    default:      _fmt_from_slice \
)(fmt)

#define printf(fmt, ...) _printf(FORMAT_TO_SLICE(fmt) __VA_OPT__(,) __VA_ARGS__)
#define sprintf(buf,fmt, ...) _sprintf(buf,FORMAT_TO_SLICE(fmt) __VA_OPT__(,) __VA_ARGS__)

#define TO_FC_ARG_COMMA(x) to_arg(x),

#define _printf(fmt_slice, ...) ({ \
    uint32_t __args_count = N_VA_ARGS(__VA_ARGS__); \
    fc_arg_t __args[N_VA_ARGS(__VA_ARGS__) > 0 ? N_VA_ARGS(__VA_ARGS__) : 1] = \
        { FOREACH(TO_FC_ARG_COMMA, __VA_ARGS__) }; \
    vprintf(fmt_slice, (fc_args_t){.args = __args,.count = __args_count}); \
})

#define _sprintf(buf,fmt_slice, ...) ({ \
    uint32_t __args_count = N_VA_ARGS(__VA_ARGS__); \
    fc_arg_t __args[N_VA_ARGS(__VA_ARGS__) > 0 ? N_VA_ARGS(__VA_ARGS__) : 1] = \
        { FOREACH(TO_FC_ARG_COMMA, __VA_ARGS__) }; \
    vsprintf(buf,fmt_slice, (fc_args_t){.args = __args,.count = __args_count}); \
})

fc_error_t vsprintf(def_slice_t buf,def_slice_t fmt, fc_args_t args);
fc_error_t vprintf(def_slice_t fmt, fc_args_t args);
fc_error_t vfprintf(file_t file,def_slice_t fmt, fc_args_t args);

#endif /* __FLIBC_STDIO_H__ */
