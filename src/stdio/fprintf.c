#include "stdio.h"
#include "error.h"
#include "stdtypes.h"
#include "memory.h"
#include "stdarg.h"

extern fc_error_t __printf_format(def_slice_t buf,def_slice_t fmt, fc_args_t args);
extern fc_error_t __printf_size(def_slice_t fmt, fc_args_t args, uint32_t* out);

#define MAX_BUF 4096

fc_error_t vfprintf
(file_t* file,def_slice_t fmt, fc_args_t args)
{
    fc_error_t res = fce_success;
    uint32_t size = 0;
    uint8_t buf[MAX_BUF] = {0};
    uint8_t* tmp = 0;
    if ((res = __printf_size(fmt,args,&size))) { return res; }
    if (size > MAX_BUF) {
        if ((res = fc_malloc(size,&tmp))) { return res; }
    } else { tmp = buf; }
    def_slice_t sl = { .base = tmp, .count = size };
    if((res = __printf_format(sl,fmt,args))) { return res; }
    res = fwrite(file,sl);
    if (size > MAX_BUF) {
        fc_error_t res2 = fc_free(&tmp);
        return (res) ? res : res2;
    }
    return res;
}
