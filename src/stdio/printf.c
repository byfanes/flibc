#include "stdio.h"
#include "error.h"
#include "stdtypes.h"
#include "memory.h"
#include "stdarg.h"

extern fc_error_t __printf_format(def_slice_t buf, def_slice_t fmt, fc_args_t args);
extern fc_error_t __printf_size(def_slice_t fmt, fc_args_t args, uint32_t* out);

fc_error_t vprintf
(def_slice_t fmt, fc_args_t args)
{
    fc_error_t res;
    uint32_t size;
    uint8_t *tmp, buf[FLIBC_STACK_THRESHOLD];
    def_slice_t sl;

    if ((res = __printf_size(fmt, args, &size))) { return res; }
    if (size > FLIBC_STACK_THRESHOLD) { if ((res = fc_malloc(size, &tmp))) { return res; } }
    else { tmp = buf; }

    set_slice(&sl, tmp, size);
    if((res = __printf_format(sl, fmt, args))) { return res; }
    res = fwrite(stdout, sl);
    if (size > FLIBC_STACK_THRESHOLD) {
        fc_error_t res2 = fc_free(&tmp);
        return (res) ? res : res2;
    }
    return res;
}
