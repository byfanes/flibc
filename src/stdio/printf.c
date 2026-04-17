#include "stdio.h"
#include "error.h"
#include "stdtypes.h"
#include "memory.h"
#include "stdarg.h"
#include "syscall.h"

extern fc_error_t __printf_format(def_slice_t buf,def_slice_t fmt, fc_args_t args);
extern fc_error_t __printf_size(def_slice_t fmt, fc_args_t args, uint32_t* out);

fc_error_t vprintf
(def_slice_t fmt, fc_args_t args)
{
    fc_error_t res = fce_success;
    uint32_t size = 0;
    char buf[4096] = {0};
    char* tmp = 0;
    if ((res = __printf_size(fmt,args,&size))) { return res; }
    if (size > 4096) {
        if ((res = fc_malloc(size,(void**)&tmp))) { return res; }
    } else { tmp = buf; }
    def_slice_t sl = {(byte_t*)tmp,size};
    if((res = __printf_format(sl,fmt,args))) { return res; }
    syscall_3(syscall_write,UNIX_STDOUT,sl.base,size);
    if (size > 4096) {
        if ((res = fc_free((void**)&tmp))) { return res; }
    }
    return res;
}
