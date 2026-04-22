#include "stdio.h"
#include "syscall.h"

extern fc_error_t __printf_format(def_slice_t buf, def_slice_t fmt, va_list va);
extern fc_error_t __printf_size(def_slice_t fmt, uint32_t* out, va_list va);

fc_error_t vprintf_sl
(def_slice_t fmt, va_list va)
{
    va_list va_c;
    fc_error_t res = fce_success;
    uint32_t size = 0;
    int32_t ret = 0;
    uint8_t *tmp = 0, buf[FLIBC_STACK_THRESHOLD] = {0};
    def_slice_t sl = {0};

    va_copy(va_c, va);
    if ((res = __printf_size(fmt, &size, va_c))) { return res; }
    if (size > FLIBC_STACK_THRESHOLD) { if ((res = fc_malloc(size, &tmp))) { return res; } }
    else { tmp = buf; }

    set_slice(&sl, tmp, size);
    if((res = __printf_format(sl, fmt, va))) { return res; }
    ret = (int32_t) syscall_3(syscall_write, UNIX_STDOUT, (arch_t)sl.base, sl.count);
    if (ret < 0) { res = fce_fwrite_failed; }
    if (ret == (int32_t)sl.count) { res = fce_success; }
    if (ret != (int32_t)sl.count) { res = fce_fwrite_partial; }
    if (size > FLIBC_STACK_THRESHOLD) {
        fc_error_t res2 = fc_free(&tmp);
        return (res) ? res : res2;
    }
    return res;
}
